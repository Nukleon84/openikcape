#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
#include "uom.h"
#include "thermodynamics.h"
using namespace std;

namespace Thermodynamics
{

    namespace Types
    {
         double Quantity::convert_to(Thermodynamics::UOM::Unit otherUnit)
         {
             return this->unit.convert_value( this->amount,otherUnit);
         }

         void Quantity::assign_value(double value, Thermodynamics::UOM::Unit otherUnit)
         {
             double converted_value= otherUnit.convert_value(value, this->unit);
             this->amount=converted_value;
         }


    }
}
