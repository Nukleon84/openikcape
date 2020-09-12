#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include "include/thermodynamics.h"
#include "include/activityProperties.h"
#include "include/vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {
        ActivityProperties ActivityCoefficients(ActivityArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            switch (sys->approach)
            {
            case EquilibriumApproach::GammaPhi:
                switch (sys->activityMethod)
                {
                case ActivityMethod::NRTL:
                    return calculateNRTL(args, sys);
                    break;

                default:
                    break;
                }
            default:
                break;
            }
            return ActivityProperties();
        }

        VectorXReal KValues(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            VectorXReal result = VectorXReal(sys->NC);

            ActivityProperties lprops;
            FugacityProperties vprops;
            ActivityArguments act_args;
            act_args.T = args.T;
            act_args.P = args.P;
            act_args.x = args.x;

            switch (sys->approach)
            {
            case EquilibriumApproach::GammaPhi:
            {

                switch (sys->activityMethod)
                {
                case ActivityMethod::NRTL:
                    lprops = calculateNRTL(act_args, sys);
                    break;
                default:
                    break;
                }

                switch (sys->fugacityMethod)
                {

                default:
                    //Assume ideal gas phase for every system
                    vprops.phi = VectorXReal::Ones(sys->NC);
                    vprops.lnphi = VectorXReal::Zero(sys->NC);
                    vprops.Gex = 0;
                    vprops.Hex = 0;
                    break;
                }

                for (int i = 0; i < sys->NC; i++)
                {
                    auto vp = PureFunctions::get_pure_property(PureProperties::VaporPressure, i, args.T, sys);
                    result[i] = lprops.gamma[i] * args.x[i] * vp / (vprops.phi[i] * args.P);
                }
            }
            default:
                break;
            }

            return result;
        }

    } // namespace VLEQFunctions
} // namespace Thermodynamics
