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
            std::wstring symbol;
            std::wstring name;            
            Thermodynamics::UOM::Unit unit;
            double amount;            

            Quantity(std::wstring symbol, std::wstring name, double amount, Thermodynamics::UOM::Unit baseUnit):
            symbol(symbol) ,
            name(name),
            unit(baseUnit),
            amount(amount)
            {
            }

            double convert_to(Thermodynamics::UOM::Unit otherUnit);
            void assign_value(double value, Thermodynamics::UOM::Unit otherUnit);
            
        };

    } // namespace Types
} // namespace Thermodynamics
