#include <iostream>
#include <math.h>
#include "lib/autodiff/forward.hpp"

#include "include/thermodynamics.h"
#include "include/purefunctions.h"
#include "include/vleqfunctions.h"
#include "include/uom.h"
#include "include/unitsets.h"
#include "include/quantity.h"

using namespace autodiff;
using namespace std;
using namespace Thermodynamics::UOM;
using namespace Thermodynamics::UOM::SI;


int main()
{
    
    auto molw = Thermodynamics::Types::Quantity(L"MW", L"MolarWeight", 18.1,SI::kg / SI::kmol );

    auto otherMwUnit=kg/mol;

    printf("MolarWeight %10.4f %ls\n", molw.amount, molw.unit.symbol.c_str());
    printf("MolarWeight %10.4f %ls\n", molw.unit.convert_value( molw.amount, kg/mol) , (kg/mol).symbol.c_str());

    auto Q = Thermodynamics::Types::Quantity(L"Q", L"Duty", 21.4, kW );
    printf("Duty %10.4f %ls\n", Q.unit.convert_value( Q.amount,W) , W.symbol.c_str());
    printf("Duty %10.4f %ls\n", Q.amount , Q.unit.symbol.c_str());
    printf("Duty %10.4f %ls\n", Q.unit.convert_value( Q.amount,MW) , MW.symbol.c_str());


    return 0;
}
