#include <iostream>
#include <math.h>
#include "lib/autodiff/forward.hpp"

#include "include/thermodynamics.h"
#include "include/purefunctions.h"
#include "include/vleqfunctions.h"

using namespace autodiff;
using namespace std;

int main()
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

    dual T, p = 1.013e5;
    int colwidth = 10;

    printf("%*s %*s %*s \n", colwidth, "T", colwidth, "K_Ethanol", colwidth, "K_Water");

    for (size_t i = 0; i < 12; i++)
    {
        T = 273.15 + i * 10;
        dual k[2];
        double df1dx = derivative(Thermodynamics::VLEQFunctions::KValue<dual>, wrt(T), at(T, p, s1), k[0]);
        double df2dx = derivative(Thermodynamics::VLEQFunctions::KValue<dual>, wrt(T), at(T, p, s2), k[1]);
        printf("%*.2f %*.3f %*.3f \n", colwidth, T.val, colwidth, k[0].val, colwidth, k[1].val);
    }

    return 0;
}
