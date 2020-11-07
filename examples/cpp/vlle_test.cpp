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
    auto sys = Thermodynamics::Types::ThermodynamicSystem("Test", db, {"Aniline", "Water"});
    auto calculator = Thermodynamics::Types::Calculator(sys);

    double T = 353.15, p = 1.013e5;
    int colwidth = 10;

    sys.substances[0].phaseL1split=0.1;
    sys.substances[1].phaseL1split=0.9;

    cout << "OpenIKCAPE VLLE Test " << endl<< endl;
    auto result = calculator.calc_flash3_tp(T, p, {0.5, 0.5});

    cout << "Temperature    : " << result.T << endl;
    cout << "Pressure       : " << result.P << endl;
    cout << "Phase State    : " << result.phase << endl;
    cout << "Vapor Fraction : " << result.vf << endl;
    cout << "L1    Fraction : " << result.l1f << endl;
    cout << "L2    Fraction : " << result.l2f << endl;

    cout << "z              : ";
    for (auto i: result.z)
        cout << i << ' ';
    cout << endl;
    
    cout << "x1             : ";
    for (auto i: result.x1)
        cout << i << ' ';
    cout << endl;
    cout << "x2             : ";
    for (auto i: result.x2)
        cout << i << ' ';
    cout << endl;
    cout << "y              : ";
    for (auto i: result.y)
        cout << i << ' ';
    cout << endl;




}
