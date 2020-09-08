import sys
sys.path.append('../bin')
sys.path.append('bin')

import openikcape as ikc
import streamlit as st
import pandas as pd
import numpy 
import altair as alt

db= ikc.loadDatabase("bin/prop.dat")
sys=ikc.createSystem("test",db,["Ethanol","Water", "Acetone","Benzene","Toluene"])
calc=ikc.createCalculator(sys)

propertyMap={}
propertyMap['VP']='Vapor Pressure [mbar]'
propertyMap['CL']='Liquid Heat Capacity [kJ/kmol/K]'
propertyMap['CPID']='Ideal Gas Heat Capacity [kJ/kmol/K]'
propertyMap['HVAP']='Heat of Vaporization [kJ/kmol]'
propertyMap['DENL']='Liquid Density [kmol/m³]'
propertyMap['KLIQ']='Liquid Heat Conductivity [W/m/K]'
propertyMap['KVAP']='Vapor Heat Conductivity [W/m/K]'
propertyMap['VISL']='Liquid Viscoty [Pa*s]'
propertyMap['VISV']='Vapour Viscoty [Pa*s]'
propertyMap['ST']='Surface Tension [N/m]'

convertMap={}
convertMap['VP']=1e-2
convertMap['CL']=1e-3
convertMap['CPID']=1e-3
convertMap['HVAP']=1e-3
convertMap['DENL']=1
convertMap['KLIQ']=1
convertMap['KVAP']=1
convertMap['VISL']=1
convertMap['VISV']=1
convertMap['ST']=1



complist=[c.name for c in sys.getComponentList()]

prop=st.sidebar.selectbox("Select the property", ["VP","CL","CPID","HVAP","DENL","KLIQ","KVAP","VISL","VISV","ST"], index=0)

comp=st.sidebar.multiselect("Select the substances", complist)
Tmin, Tmax =st.sidebar.slider('Temperature Range [°C]', 0, 400, [50, 150])

steps =st.sidebar.slider('Number of Steps', 0, 50,20)

yscale =st.sidebar.radio('Y-Axis Scale',['Normal', 'Log'], index=0)
xscale =st.sidebar.radio('X-Axis Scale',['Normal', '1/T'], index=0)

T=[]
y=[]
if(len(comp)>0):
    for i in range(steps):
        Ti=Tmin+(Tmax-Tmin)*(i+1)/steps
        
        T.append(Ti if xscale=='Normal' else 1/Ti)

    for c in comp:
        index=complist.index(c)
        yc=[]
        for i in range(steps):       
            Ti=Tmin+(Tmax-Tmin)*(i+1)/steps
            yi=calc.getPureProperty(prop, index, Ti+273.15)        
            yc.append(yi*convertMap[prop])
        y.append(yc)

    data=numpy.array(y)

    df= pd.DataFrame(data.T, index=pd.Index(T,name="x"), columns=comp)
    source = df.reset_index().melt('x', var_name='component', value_name='y')

    #st.line_chart(df)
    line_chart = alt.Chart(source).mark_line(interpolate='basis').encode(
        alt.X('x', title='Temperature [°C]'),
        alt.Y('y', title=propertyMap[prop],  scale= alt.Scale(type='log') if yscale=='Log' else alt.Scale()  ),
        color='component:N'
    ).properties(
        title='Property Chart',
        width=800,
        height=600
    )

    st.altair_chart(line_chart)
    st.dataframe(df)