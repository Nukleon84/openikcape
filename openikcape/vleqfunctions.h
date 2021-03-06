#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>

#include "thermodynamics.h"
#include "activityProperties.h"
#include "purefunctions.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {

        ActivityProperties calculateNRTL(Real T, Real p, VectorXReal x, const Thermodynamics::Types::ThermodynamicSystem *sys);
        ActivityProperties ActivityCoefficients(Real T, Real p, VectorXReal x, const Thermodynamics::Types::ThermodynamicSystem *sys);
        FugacityProperties FugacityCoefficients(Real T, Real p, VectorXReal y, const Thermodynamics::Types::ThermodynamicSystem *sys);
     
        VectorXReal KValues(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);
     
        EquilibriumProperties calculate_flash_TP(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);
        EquilibriumProperties calculate_flash_ZP(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);
         EquilibriumProperties calculate_flash_ZT(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);

         
        Equilibrium3Properties calculate_flash3_TP(Equilibrium3Arguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);

        VectorXReal WilsonKFactors(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys);
  

        template <typename T>
        T KValue(T temperature, T pressure, const Thermodynamics::Types::Substance &s)
        {

            auto f = s.functions.find(Thermodynamics::Types::PureProperties::VaporPressure);

            if (f == s.functions.end())
                throw new runtime_error("Substance does not contain a function for pure property <VaporPressure>");

            switch (f->second.correlation)
            {
            case Thermodynamics::Types::PureCorrelations::Antoine:
                return Thermodynamics::PureFunctions::ANTO(temperature, f->second) / pressure;
                break;
            case Thermodynamics::Types::PureCorrelations::ExtendedKirchhoff:
                return Thermodynamics::PureFunctions::KIR1(temperature, f->second) / pressure;
                break;

            default:
                return 1e-10;
                break;
            }
        }
    } // namespace VLEQFunctions
} // namespace Thermodynamics