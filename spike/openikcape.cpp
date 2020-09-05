#include "lib/pybind11/pybind11.h"

#include <iostream>
#include <math.h>
#include "lib/autodiff/forward.hpp"

#include "include/thermodynamics.h"
#include "include/purefunctions.h"
#include "include/vleqfunctions.h"

using namespace autodiff;
using namespace std;

Thermodynamics::Types::Substance get_component(string component)
{
    auto f1 = Thermodynamics::Types::PureFunction();
    f1.correlation = Thermodynamics::Types::PureCorrelations::Antoine;
    f1.property = Thermodynamics::Types::PureProperties::VaporPressure;
    f1.c = {2.31553586E+01, 3.46253549E+03, -5.36319937E+01};

    auto s1 = Thermodynamics::Types::Substance();
    s1.name = L"Ethanol";
    s1.formula = L"C2H5O";
    s1.functions[Thermodynamics::Types::PureProperties::VaporPressure] = f1;

    auto f2 = Thermodynamics::Types::PureFunction();
    f2.correlation = Thermodynamics::Types::PureCorrelations::Antoine;
    f2.property = Thermodynamics::Types::PureProperties::VaporPressure;
    f2.c = {2.33275405E+01, 3.91170311E+03, -4.18495115E+01};

    auto s2 = Thermodynamics::Types::Substance();
    s2.name = L"Water";
    s2.formula = L"H2O";
    s2.functions[Thermodynamics::Types::PureProperties::VaporPressure] = f2;

    if (component == "Ethanol")
        return s1;

    if (component == "Water")
        return s2;

    return s2;
}

tuple<double, double> kvalue(Thermodynamics::Types::Substance component, double temp, double pres)
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

PYBIND11_MODULE(openikcape, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    pybind11::class_<Thermodynamics::Types::Substance>(m, "Substance")
        .def(pybind11::init<>())
        .def_readwrite("name", &Thermodynamics::Types::Substance::name)
        .def_readwrite("casno", &Thermodynamics::Types::Substance::casNo)
        .def_readwrite("formula", &Thermodynamics::Types::Substance::formula);




    m.def("add", &add, "A function which adds two numbers");

    m.def("kvalue", &kvalue, "A function which calculates the vle partition coefficient");

    m.def("get_component", &get_component, "A function which returns a substance for a given string");
}