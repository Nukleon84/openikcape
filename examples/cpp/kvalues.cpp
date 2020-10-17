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

    dual T, p = 1.013e5;
    int colwidth = 10;

    printf("%*s %*s %*s \n", colwidth, "T", colwidth, "K_Ethanol", colwidth, "K_Water");

    for (size_t i = 0; i < 12; i++)
    {
        T = 273.15 + i * 10;
        dual k[2];
        double df1dx = derivative(Thermodynamics::VLEQFunctions::KValue<dual>, wrt(T), at(T, p, sys.get_substances()[0]), k[0]);
        double df2dx = derivative(Thermodynamics::VLEQFunctions::KValue<dual>, wrt(T), at(T, p, sys.get_substances()[1]), k[1]);
        printf("%*.2f %*.3f %*.3f \n", colwidth, T.val, colwidth, k[0].val, colwidth, k[1].val);
    }

    return 0;
}
