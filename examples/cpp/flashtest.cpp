#include <iostream>
#include <math.h>
#include "autodiff/forward.hpp"

#include "thermodynamics.h"
#include "vleqfunctions.h"

using namespace autodiff;
using namespace std;

int main()
{
    auto db = Thermodynamics::Types::Database("prop.dat");
    auto sys = Thermodynamics::Types::ThermodynamicSystem("Test", db, {"Methanol", "Water"});
    auto calculator = Thermodynamics::Types::Calculator(sys);

    double T = 353.15, p = 1.013e5;
    int colwidth = 10;

    auto result = calculator.calc_flash_tp(T, p, {0.5, 0.5});

    cout << "Phase State    :" << result.phase << endl;
    cout << "Vapor Fraction :" << result.vf << endl;
    cout << "Temperature:" << result.T << endl;

    auto result2 = calculator.calc_flash_zp(0.0, p, {0.5, 0.5});

    cout << "Phase State    :" << result2.phase << endl;
    cout << "Vapor Fraction :" << result2.vf << endl;
    cout << "Temperature:" << result2.T << endl;

    result2 = calculator.calc_flash_zp(1.0, p, {0.5, 0.5});

    cout << "Phase State    :" << result2.phase << endl;
    cout << "Vapor Fraction :" << result2.vf << endl;
    cout << "Temperature:" << result2.T << endl;

    result2 = calculator.calc_flash_zt(0.0,T, {0.5, 0.5});

    cout << "Phase State    :" << result2.phase << endl;
    cout << "Vapor Fraction :" << result2.vf << endl;
    cout << "Temperature:" << result2.T << endl;
    cout << "Pressure:" << result2.P << endl;




}
