#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>

#include "uom.h"
using namespace std;

namespace Thermodynamics
{
    namespace UOM
    {
        double Unit::get_conversion_factor(Unit other)
        {
            return this->factor / other.factor;
        }
        
        double Unit::convert_value(double value, Unit target)
        {
            double baseValue = this->factor * value + this->offset;
            return (baseValue - target.offset) / target.factor;
        }

        Unit Unit::operator*(const Unit rhs)
        {
            auto newDims = std::array<double, 8>();

            for (int i = 0; i < 8; i++)
            {
                newDims[i] = this->dimensions[i] + rhs.dimensions[i];
            }

            return Unit(this->symbol + "*" + rhs.symbol, "Derived Unit", newDims, this->factor * rhs.factor, this->offset + rhs.offset);
        }
        Unit Unit::operator/(const Unit rhs)        
        {
            auto newDims = std::array<double, 8>();

            for (int i = 0; i < 8; i++)
            {
                newDims[i] = this->dimensions[i] - rhs.dimensions[i];
            }

            return Unit(this->symbol + "/" + rhs.symbol, "Derived Unit", newDims, this->factor / rhs.factor, this->offset - rhs.offset);
        }
        Unit Unit::operator^(double rhs)       
        {
            auto newDims = std::array<double, 8>();

            for (int i = 0; i < 8; i++)
            {
                newDims[i] = this->dimensions[i] * rhs;
            }

            return Unit(this->symbol + "^" + std::to_string(rhs), "Derived Unit", newDims, this->factor, this->offset);
        }

        Unit::operator std::string() const
        {
            return this->symbol;
        }

    } // namespace UOM
} // namespace Thermodynamics
