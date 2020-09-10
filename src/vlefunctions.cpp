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
    }
}

       