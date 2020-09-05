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

void printQuantity(Thermodynamics::Types::Quantity &quantity)
{
    printf("%ls %10.4f %ls\n", quantity.symbol.c_str(), quantity.amount, quantity.unit.symbol.c_str());
}

int main()
{

    auto molw = Thermodynamics::Types::Quantity(L"MW", L"MolarWeight", 18.1, SI::kg / SI::kmol);

    auto otherMwUnit = kg / mol;

    printf("MolarWeight %10.4f %ls\n", molw.amount, molw.unit.symbol.c_str());
    printf("MolarWeight %10.4f %ls\n", molw.convert_to(kg / mol), (kg / mol).symbol.c_str());

    auto Q = Thermodynamics::Types::Quantity(L"Q", L"Duty", 21.4, kW);
    printf("Q %10.4f %ls\n", Q.convert_to(W), W.symbol.c_str());
    printQuantity(Q);
    printf("Q %10.4f %ls\n", Q.convert_to(MW), MW.symbol.c_str());

    auto mass = Thermodynamics::Types::Quantity(L"m", L"Mass", 1, kg);

    printQuantity(mass);
    printf("m %10.4f %ls\n", mass.convert_to(USENG::lb), (USENG::lb).symbol.c_str());

    printf("Assign new value 1lb to mass\n");
    mass.assign_value(1.0, USENG::lb);
    printQuantity(mass);

    auto mass2 = Thermodynamics::Types::Quantity(L"m2", L"Mass", 1, USENG::lb);

    printQuantity(mass2);
    printf("m2 %10.4f %ls\n", mass2.convert_to(kg), kg.symbol.c_str());

    printf("Assign new value 1kg to mass\n");
    mass2.assign_value(1.0, kg);
    printQuantity(mass2);


    auto temp = Thermodynamics::Types::Quantity(L"T", L"Temperature", 298.15, K);
    printQuantity(temp);
    temp.assign_value(100.0, METRIC::C);
    printQuantity(temp);
    printf("T %10.4f %ls\n", temp.convert_to(METRIC::C), (METRIC::C).symbol.c_str());
    return 0;
}
