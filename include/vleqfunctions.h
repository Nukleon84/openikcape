#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include "include/thermodynamics.h"
#include "include/substance.h"
using namespace std;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {
        template <typename T>
        T KValue(T temperature, T pressure, const Thermodynamics::Types::Substance &s)
        {

            auto f = s.functions.find(Thermodynamics::Types::PureProperties::VaporPressure);

            if(f==s.functions.end())
                throw new runtime_error("Substance does not contain a function for pure property <VaporPressure>");

            switch (f->second.correlation)
            {
            case Thermodynamics::Types::PureCorrelations::Antoine:
                return PureFunctions::ANTO(temperature, f->second) / pressure;
                break;

            default:
                return 1e-10;
                break;
            }
        }
    } // namespace VLEQFunctions
} // namespace Thermodynamics