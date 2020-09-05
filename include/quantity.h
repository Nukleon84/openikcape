#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
#include "include/uom.h"
using namespace std;

namespace Thermodynamics
{

    namespace Types
    {
        struct Quantity
        {
            std::wstring name;
            std::wstring symbol;
            double amount;
            Thermodynamics::UOM::Unit unit;

            Quantity(std::wstring symbol, std::wstring name, double amount, Thermodynamics::UOM::Unit baseUnit):
            symbol(symbol) ,
            name(name),
            unit(baseUnit),
            amount(amount)
            {
            }

        };

    } // namespace Types
} // namespace Thermodynamics
