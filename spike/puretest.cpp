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
    auto db= Thermodynamics::Types::Database("prop.dat");
    auto sys =Thermodynamics::Types::ThermodynamicSystem("Test",db,{"Ethanol","Water"});
    auto calculator = Thermodynamics::Types::Calculator(sys);

    double T, p = 1.013e5;
    int colwidth = 10;

    printf("%*s %*s %*s \n", colwidth, "T", colwidth, "K_Ethanol", colwidth, "K_Water");

    for (size_t i = 0; i < 12; i++)
    {
        T = 273.15 + i * 10;
        double y0= calculator.get_pure_property("VP",0, T)        ;
        double y1= calculator.get_pure_property("VP",1, T)        ;
        
        printf("%*.2f %*.3f %*.3f \n", colwidth, T, colwidth, y0, colwidth, y1);
    }

    return 0;
}
