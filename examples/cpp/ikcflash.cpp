#include <iostream>
#include <math.h>
//#include "autodiff/forward.hpp"

#include "openikcape.h"


using namespace autodiff;
using namespace std;

int main(int argc, char *argv[])
{
    auto db = Thermodynamics::Types::Database("prop.dat");
    auto sys = Thermodynamics::Types::ThermodynamicSystem("Test", db, {"Methanol", "Water"});
    auto calculator = Thermodynamics::Types::Calculator(sys);

    double T = 353.15, p = 1.013e5, x1=0.5;
    cout << "You called the IKCFLASH executable with " << argc << " arguments" << endl;
    if ( argc == 4 ) 
	{
		T = stod( argv[1] );
		p = stod( argv[2] );
		x1 = stod( argv[3] );        
	}

    auto result = calculator.calc_flash_tp(T, p, {x1, 1.0-x1});

    cout << "Phase State    :" << result.phase << endl;
    cout << "Vapor Fraction :" << result.v << endl;
    cout << "Temperature:" << result.T << endl;
    cout << "Pressure:" << result.P << endl;
    
    cout << "z: ";
    for (auto i: result.z)
        cout << i << ' ';
    cout << endl;
    
    cout << "x: ";
    for (auto i: result.x)
        cout << i << ' ';
    cout << endl;
   
    cout << "y: ";
    for (auto i: result.y)
        cout << i << ' ';
    cout << endl;

}
