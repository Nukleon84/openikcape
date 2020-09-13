import sys
sys.path.append('../bin')
sys.path.append('bin')

import openikcape as ikc
import streamlit as st
import pandas as pd
import numpy 
import altair as alt

db= ikc.loadDatabase("bin/prop.dat")


complist=[c for c in db.getComponentList()]

mode=["Gamma&Gex", "IsobaricVLE", "IsothermalVLE"]

comp1=st.sidebar.selectbox("Select the first substance", complist, index=0)
comp2=st.sidebar.selectbox("Select the second substance", complist, index=2)
T =st.sidebar.slider('Temperature [°C]', 0, 400, 100)
P =st.sidebar.slider('Temperature Pressure [mbar]', 10, 5000, 1000)

steps =st.sidebar.slider('Number of Steps', 2, 30,10)

mode=st.sidebar.selectbox("Select the calculation mode", mode, index=0)

sys=ikc.createSystem("test",db,[comp1,comp2])
calc=ikc.createCalculator(sys)

if(mode=="IsobaricVLE"):
    st.title("Isobaric VLE")
    tb=[]
    td=[]
    x=[]
    for i in range(steps):
        xi=(i)/(steps-1)    
        x.append(xi)
    for i in range(steps):       
        xi=(i)/(steps-1)    
        props=calc.calcFlashZP(0.0,P*1e2,[xi,1-xi])
        tb.append(props.T-273.15)       
        props=calc.calcFlashZP(1.0,P*1e2,[xi,1-xi])
        td.append(props.T-273.15)       
    
    data=numpy.array([tb,td])
    df= pd.DataFrame(data.T, index=pd.Index(x,name="x"), columns=["Bubble Point", "Dew Point"])
    source = df.reset_index().melt('x', var_name='curve', value_name='y')
    line_chart = alt.Chart(source).mark_line(interpolate='basis').encode(   
        alt.X('x', title='x1 [mol/mol]'),
        alt.Y('y', title="Temperature [°C]"),    
        color='curve:N'
    ).properties(
        title=f'Isobaric Phase Envelope (at {P} mbar)',
        width=400,
        height=400
    ).configure_legend(
    orient='bottom'
    )
    st.altair_chart(line_chart)

if(mode=="IsothermalVLE"):
    st.title("Isothermal VLE")
    tb=[]
    td=[]
    x=[]
    for i in range(steps):
        xi=(i)/(steps-1)    
        x.append(xi)
    for i in range(steps):       
        xi=(i)/(steps-1)    
        props=calc.calcFlashZT(0.0,T+273.15,[xi,1-xi])
        tb.append(props.P/1e2)       
        props=calc.calcFlashZT(1.0,T+273.15,[xi,1-xi])
        td.append(props.P/1e2)       
    
    data=numpy.array([tb,td])
    df= pd.DataFrame(data.T, index=pd.Index(x,name="x"), columns=["Bubble Point", "Dew Point"])
    source = df.reset_index().melt('x', var_name='curve', value_name='y')
    line_chart = alt.Chart(source).mark_line(interpolate='basis').encode(   
        alt.X('x', title='x1 [mol/mol]'),
        alt.Y('y', title="Pressure [mbar]"),    
        color='curve:N'
    ).properties(
        title=f'Isothermal Phase Envelope (at {T} °C)',
        width=400,
        height=400
    ).configure_legend(
    orient='bottom'
    )
    st.altair_chart(line_chart)


if(mode=="Gamma&Gex"):
    st.title("Activity Coefficients")
    x=[]
    gamma=[]
    for i in range(steps):
        xi=(i)/(steps-1)    
        x.append(xi)

    gex=[]
    g1=[]
    g2=[]
    for i in range(steps):       
        xi=(i)/(steps-1)    
        props=calc.getActivityCoefficients(T+273.15,1e5,[xi,1-xi])       

        gex.append(props.Gex/(8.31433*(T+273.15)))
        g1.append(props.gamma[0])
        g2.append(props.gamma[1])

    data=numpy.array([g1,g2])

    df= pd.DataFrame(data.T, index=pd.Index(x,name="x"), columns=[comp1, comp2])
    source = df.reset_index().melt('x', var_name='component', value_name='y')


    #st.line_chart(df)
    line_chart = alt.Chart(source).mark_line(interpolate='basis').encode(
        alt.X('x', title='x1 [mol/mol]'),
        alt.Y('y', title="Activity Coefficient"),    
        color='component:N'
    ).properties(
        title='Activity Coefficients',
        width=400,
        height=400
    ).configure_legend(
    orient='bottom'
    )
    st.altair_chart(line_chart)
    data2=numpy.array([gex])
    df2= pd.DataFrame(data2.T, index=pd.Index(x,name="x"), columns=["Gex"])
    source2 = df2.reset_index().melt('x', var_name='component', value_name='y')
    #st.write(source2)
    line_chart2 = alt.Chart(source2).mark_line(interpolate='basis').encode(
        alt.X('x', title='x1 [mol/mol]'),
        alt.Y('y', title="Gex/(RT) [-]")
        
    ).properties(
        title='Excess Gibbs Energy',
        width=400,
        height=400
    )

    st.altair_chart(line_chart2)


#st.dataframe(df)