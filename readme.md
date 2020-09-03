# Welcome to the OpenIKCAPE Project Repository

## Synopsis

This project aims to be an open-source re-implementation of the IK-CAPE Thermodynamics Module, which can be found at the homepage of the DECHEMA e.V.
(https://dechema.de/en/Media/Engineering+Software/IK_CAPE+THERMO-p-40.html)

A bit of history can be found on the Dechema homepage.

> The IK-CAPE Thermodynamics-Module has been developed from the members of the german Industrie Konsortium CAPE (Industrial Cooperation Computer Aided Process Engineering). IK-CAPE's mission is to define open system standards on the fields of Computer Aided Process Engineering. Members of IK-CAPE are the companies BASF, Bayer, Hoechst, Degussa-Hüls and Dow. Main aim of the Thermodynamics-Module development was the creation of an efficient and full featured program package for thermodynamic calculations.

## Mission Statement

This project aims to develop a reference thermodynamic library that can be embedded in Process Simulators or used as a stand-alone application for the calculation of the properties of gases and liquids at different conditions. This library does not provide any property data, which have to given by the user in the form of input files.

##  Scope and Content
The IK-CAPE represent a set of equations that can be used to model multi-component phase equilibria using equation-of-state or activitiy coefficient models. The original IK-CAPE module is implemented in Fortran and distributed by the Dechema e.V. This projects aims to develop an open-source, community-driven implementation in Modern C++, using new features like Automatic Differentiation, Template Metaprogramming, Containers, managed pointers and other useful things that make working in C++ much more productive than in Fortran77.

Furthermore, this library will include reference implementations for phase equilibrium calculation routines ("flash algorithms") in order to enable users to use the IK-CAPE directly without the need for a process simulator or having to implement their own flash algorithms (although this will definitely be an option).

In later stages Python bindings will be developed to simplify the creation of applications based on this library.

The [collection of formulas](https://dechema.de/dechema_media/Downloads/Informationssysteme/IK_CAPE_Equations-p-888.pdf) describe the following models and equations. The implementation is based purely on the publicly available information.


### Temperature dependent properties  	

* Polynom
* Polynom as exponent
* Antoine equation
*    extended Antoine equation
*    Watson equation
*    Wagner equation
*    Sutherland equation
*    Kirchhoff equation
*    HOECHST: equation for specific heat capacity of a liquid
*    HOECHST: equation for dynamic viscosity
*    Rackett equation, DIPPR style
*    Aly-Lee equation
*    extended Kirchhoff equation, DIPPR style
*    DIPPR equation for heat of vaporization and surface tension
*    DIPPR equation for heat conductivity and viscosity of a gas

### Averages in mixtures
  	
*    averages on molar basis
*    averages on weight basis
*    averages on logarithmic molar basis
*    averages on logaritmic weight basis
*    average of density via volume
*    special method for averages of gas heat conductivities
*    special method for averages of gas viscosities
*    average from Wilke for gas viscosities
*    average form Wassiljewa, Mason, Saxena for gas heat conductivities
*    special method for averages on surface tensions, DIPPR style
*    special method for averages on liquid heat conductivities, DIPPR style

### Activity coefficients  	

*    ideal
*    NRTL
*    UNIQUAC
*    Wilson
*    Flory-Huggins
*    UNIFAC

### Fugacity coefficients  	

*    ideal
*    Peng-Robinson
*    Redlich-Kwong-Soave
*    virial equation
*    assoziation in gas phase

### Chemical reactions
  
*    given reaction coordinate
*    given conversion related to starting composition
*    given conversion related to end composition
*    equilibrium reaction in liquid phase as function of mole fractions
*    equilibrium reaction in vapor phase as function of mole fractions
*    equilibrium reaction in liquid phase as function of concentration
*    equilibrium reaction in vapor phase as function of concentration
*    equilibrium reaction in liquid phase as function of activity coefficients
*    equilibrium reaction in vapor phase as function of partial pressures
*    equilibrium reaction in liquid phase as function of fugacity
*    equilibrium reaction in vapor phase as function of fugacity
*    kinetically controlled reaction in liquid phase as function of mole fraction
*    kinetically controlled reaction in vapor phase as function of mole fraction
*    kinetically controlled reaction in liquid phase as function of fraction
*    kinetically controlled reaction in vapor phase as function of fraction
*    kinetically controlled reaction in liquid phase as function of mass
*    kinetically controlled reaction in vapor phase as function of mass

## Examples

(These functionality for these examples is currently not implemented, and they should only demonstrate how I envision this library to be used in the end.)
### C++17
```c++
#include "openikcape.h"

auto componentList={"Ethanol", "Water", "Acetone"};

auto db= ikcape::load_database("prop.dat");
auto sys= ikcape::create_system("System 1", "VLE", "NRTL", db, componentList);
auto calc= ikcape::create_calculator(sys);

double pLV[3],hL[3],hV[3];
for(int i=0;i<10;i++)
{
    calc.get_pure_property("VP", -1, 273.15+10*i, pLV);
    calc.get_pure_enthalpy("L", -1, 273.15+10*i, 1e5,hL );
    calc.get_pure_enthalpy("V", -1, 273.15+10*i, 1e5,hV );
    fprintf(...)
}

FlashResult res= ikcape::solve_flash_tpz(sys, 365.15, 1.013e5, {0.5, 0.5, 0} );
fprintf("Vapor fraction: %g", res.vf);
fprintf("Phase State: %s", res.phase_state);
calc.release()
sys.release()
db.release()
```

### Python
```python
import openikcape

componentList=["Ethanol", "Water", "Acetone"]

db= ikcape.load_database("prop.dat")
sys= ikcape.create_system("System 1", "VLE","NRTL" db, componentList)
calc= ikcape.create_calculator(sys)

for i in range(10):
    #Ask for properties for all components with index -1
    #pLV is list of double of length NC
    pLV = calc.get_pure_property("VP", -1, 273.15+10*i) 
    hL = calc.get_pure_enthalpy("L", -1, 273.15+10*i, 1e5 )
    hV = calc.get_pure_enthalpy("V", -1, 273.15+10*i, 1e5 )
    fprintf(...)


res= ikcape::solve_flash_tpz(sys, 365.15, 1.013e5, [0.5, 0.5, 0] )
print(f"Vapor fraction: {res.vf}" )
print(f"Phase State: {res.phase_state}")
```

## Acknowledgements

This library uses the AutoDiff library written by Allan Leal (https://autodiff.github.io/) for the calculation of the partial derivatives of the thermodynamic properties when solving equilibrium problems.

## License

> Copyright 2020 Jochen Steimel
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.