#include "lib/pybind11/pybind11.h"

#include "lib/pybind11/stl.h"



#include <iostream>
#include <math.h>
#include "lib/autodiff/forward.hpp"

#include "include/thermodynamics.h"
#include "include/purefunctions.h"
#include "include/vleqfunctions.h"

using namespace autodiff;
using namespace std;
using namespace Thermodynamics::Types;

tuple<double, double> kvalue(Substance component, double temp, double pres)
{
    dual T, p, k;
    T = temp;
    p = pres;
    double dKdT = 0;

    dKdT = derivative(Thermodynamics::VLEQFunctions::KValue<dual>, wrt(T), at(T, p, component), k);

    return std::make_tuple(k.val, dKdT);
}

int add(int i, int j)
{    
    return i + j * 2;
}


Database load_database(string file)
{
    return Database(file);
}

ThermodynamicSystem create_system(string name,Database &db, vector<string> componentlist )
{
    return ThermodynamicSystem(name,db,componentlist);
}

Calculator create_calculator(ThermodynamicSystem &system)
{
    return Calculator(system);
}





PYBIND11_MODULE(openikcape, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    pybind11::class_<Substance>(m, "Substance")
        .def(pybind11::init<>())
        .def_readwrite("name", &Substance::name)
        .def_readwrite("casno", &Substance::casNo)
        .def_readwrite("formula", &Substance::formula);
    
     pybind11::class_<ActivityPropertiesExt>(m, "ActivityProperties")
        .def(pybind11::init<>())
        .def_readwrite("gamma", &ActivityPropertiesExt::gamma)
        .def_readwrite("Gex", &ActivityPropertiesExt::Gex)
        .def_readwrite("Hex", &ActivityPropertiesExt::Gex);
 
     pybind11::class_<EquilibriumPropertiesExt>(m, "EquilibriumProperties")
        .def(pybind11::init<>())
        .def_readwrite("T", &EquilibriumPropertiesExt::T)
        .def_readwrite("P", &EquilibriumPropertiesExt::P)
        .def_readwrite("v", &EquilibriumPropertiesExt::v)
        .def_readwrite("x", &EquilibriumPropertiesExt::x)
        .def_readwrite("y", &EquilibriumPropertiesExt::y)
        .def_readwrite("z", &EquilibriumPropertiesExt::z);


    pybind11::class_<Database>(m, "Database")   
        .def(pybind11::init<std::string&>())     
        .def("getComponentList", &Database::get_component_list);
  
    pybind11::class_<ThermodynamicSystem>(m, "ThermodynamicSystem")        
        .def_readwrite("name", &ThermodynamicSystem::name)
        .def("getComponentList", &ThermodynamicSystem::get_component_list);
  
    pybind11::class_<Calculator>(m, "Calculator")           
        .def("getPureProperty", &Calculator::get_pure_property)
        .def("getActivityCoefficients", &Calculator::get_vleq_gamma)
        .def("calcFlashTP", &Calculator::calc_flash_tp)
        .def("calcFlashZP", &Calculator::calc_flash_zp)
        .def("calcFlashZT", &Calculator::calc_flash_zt);
  

    m.def("loadDatabase", &load_database, "A function which creates a thermodynamic database");
    m.def("createSystem", &create_system, "A function which creates a thermodynamic system");
    m.def("createCalculator", &create_calculator, "A function which creates a calculator object");

    m.def("add", &add, "A function which adds two numbers");
    m.def("kvalue", &kvalue, "A function which calculates the vle partition coefficient");
}