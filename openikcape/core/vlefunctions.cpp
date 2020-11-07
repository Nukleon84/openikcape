#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include "thermodynamics.h"
#include "activityProperties.h"
#include "vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {
        ActivityProperties ActivityCoefficients(Real T, Real p, VectorXReal x,  const Thermodynamics::Types::ThermodynamicSystem *sys)
        {

            switch (sys->activityMethod)
            {
            case ActivityMethod::NRTL:
                return calculateNRTL(T,p,x, sys);
                break;

            default:
                break;
            }

            return ActivityProperties();
        }

        FugacityProperties FugacityCoefficients(Real T, Real p, VectorXReal y,  const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            switch (sys->fugacityMethod)
            {

            default:
                FugacityProperties vprops;
                //Assume ideal gas phase for every system
                vprops.phi = VectorXReal::Ones(sys->NC);
                vprops.lnphi = VectorXReal::Zero(sys->NC);
                vprops.Gex = 0;
                vprops.Hex = 0;
                return vprops;
                break;
            }
            return FugacityProperties();
        }

        VectorXReal WilsonKFactors(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            VectorXReal result = VectorXReal::Zero(sys->NC);
            for (int i = 0; i < sys->NC; i++)
            {
                double Pci = sys->substances[i].constants.at(MolecularProperties::CriticalPressure).amount;
                double wi= sys->substances[i].constants.at(MolecularProperties::AcentricFactor).amount;
                double Tci= sys->substances[i].constants.at(MolecularProperties::CriticalTemperature).amount;
                result[i] = exp(log(Pci / args.P) + 5.373 * (1 + wi) * (1 - Tci / args.T));
            }
            return result;
        }

        VectorXReal KValues(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            VectorXReal result = VectorXReal(sys->NC);

            ActivityProperties lprops;
            FugacityProperties vprops;
            /*ActivityArguments act_args;
            act_args.T = args.T;
            act_args.P = args.P;
            act_args.x = args.x;

            FugacityArguments fug_args;
            fug_args.T = args.T;
            fug_args.P = args.P;
            fug_args.y = args.y;*/

            if (sys->approach == EquilibriumApproach::GammaPhi)
            {
                lprops = ActivityCoefficients(args.T, args.P, args.x, sys);
                vprops = FugacityCoefficients(args.T, args.P, args.y, sys);
                for (int i = 0; i < sys->NC; i++)
                {
                    auto vp = PureFunctions::get_pure_property(PureProperties::VaporPressure, i, args.T, sys);
                    result[i] = lprops.gamma[i] * vp / (vprops.phi[i] * args.P);
                }
            }

            return result;
        }

    } // namespace VLEQFunctions
} // namespace Thermodynamics
