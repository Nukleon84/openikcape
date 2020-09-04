#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>

#include "include/uom.h"
using namespace std;

namespace Thermodynamics
{
    namespace UOM
    {
        double Unit::get_conversion_factor(Unit other)
        {
            return 1.0;
        }

        double Unit::convert_value(double value, Unit target)
        {
            return 1.0;
        }

        Unit Unit::operator*(        // passing lhs by value helps optimize chained a+b+c
                       const Unit &rhs) // otherwise, both parameters may be const references
        {
            auto newDims=std::array<double,8>() ; 

            for (int i = 0; i < 8; i++)
            {
                newDims[i]= this->dimensions[i]+rhs.dimensions[i];
            }
            
            return Unit(L"$(a.symbol)*$(b.symbol)", L"Derived Unit", newDims,this->factor*rhs.factor,this->offset+rhs.offset);        
        }
        Unit Unit::operator/(      // passing lhs by value helps optimize chained a+b+c
                       const Unit &rhs) // otherwise, both parameters may be const references
        {
                auto newDims=std::array<double,8>() ; 

            for (int i = 0; i < 8; i++)
            {
                newDims[i]= this->dimensions[i]-rhs.dimensions[i];
            }
            
            return Unit(L"$(a.symbol)*$(b.symbol)", L"Derived Unit", newDims,this->factor*rhs.factor,this->offset+rhs.offset);        

        }
        Unit Unit::operator^(        // passing lhs by value helps optimize chained a+b+c
                       const double rhs) // otherwise, both parameters may be const references
        {
                auto newDims=std::array<double,8>() ; 

            for (int i = 0; i < 8; i++)
            {
                newDims[i]= this->dimensions[i]*rhs ;
            }
            
            return Unit(L"$(a.symbol)*$(b.symbol)", L"Derived Unit", newDims,this->factor,this->offset);        

        }

    } // namespace UOM
} // namespace Thermodynanmics
