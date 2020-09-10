#include <iostream>
#include <math.h>
#include "lib/autodiff/forward.hpp"

#include "include/thermodynamics.h"
#include "include/vleqfunctions.h"

using namespace autodiff;
using namespace std;

int main()
{
    auto db = Thermodynamics::Types::Database("prop.dat");
    auto sys = Thermodynamics::Types::ThermodynamicSystem("Test", db, {"Ethanol", "Water"});
    auto calculator = Thermodynamics::Types::Calculator(sys);

    double T=353.15, p = 1.013e5;
    int colwidth = 10;

    cout << "A:"<<endl
         << sys.binaryparameters.at("NRTL").p.at("A") << "\n";

    cout << "B:"<<endl
         << sys.binaryparameters.at("NRTL").p.at("B") << "\n";
    cout << "C:"<<endl
         <<  sys.binaryparameters.at("NRTL").p.at("C") << "\n";

cout << "D:"<<endl
         << sys.binaryparameters.at("NRTL").p.at("D") << "\n";

         cout << "E:"<<endl
         << sys.binaryparameters.at("NRTL").p.at("E") << "\n";

         cout << "F:"<<endl
         << sys.binaryparameters.at("NRTL").p.at("F") << "\n";
    int steps=10;
    cout << "Gamma Scan"<<endl;

    for (size_t i = 0; i < steps; i++)
    {
        double x1 = (double)(i)/(double)(steps-1);

          auto props = calculator.get_vleq_gamma(T, 1.0138e5, {x1, 1.0-x1});
    cout << "x: ("<< x1 <<", "<<(1.0-x1)<<") Gamma :(";
    for (auto g : props.gamma)
        cout << g << "\t";
    cout <<") Gex:"<< props.Gex/( 8.31433*T);
    cout<<endl; 
    }
    
  
    cout << "Calculation finished";
    return 0;
}
