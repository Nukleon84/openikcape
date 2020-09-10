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

comp1=st.sidebar.selectbox("Select the first substance", complist, index=0)
comp2=st.sidebar.selectbox("Select the second substance", complist, index=2)
T =st.sidebar.slider('Temperature Range [°C]', 0, 400, 100)

steps =st.sidebar.slider('Number of Steps', 0, 50,20)

sys=ikc.createSystem("test",db,[comp1,comp2])
calc=ikc.createCalculator(sys)

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
line_chart2 = alt.Chart(source2).mark_line().encode(
    alt.X('x', title='x1 [mol/mol]'),
    alt.Y('y', title="Gex/(RT) [-]")
    
).properties(
    title='Excess Gibbs Energy',
    width=400,
    height=400
)

st.altair_chart(line_chart2)


#st.dataframe(df)