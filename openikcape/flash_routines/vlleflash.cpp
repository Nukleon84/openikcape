#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "thermodynamics.h"
#include "activityProperties.h"
#include "vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;
using namespace autodiff;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {

          Equilibrium3Properties calculate_flash3_TP(Equilibrium3Arguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            Equilibrium3Properties props;
            props.T = args.T;
            props.P = args.P;
            props.vf = 0.5;
            props.x1 = VectorXReal(args.x1);
            props.x2 = VectorXReal(args.x2);
            props.y = VectorXReal(args.y);
            props.z = VectorXReal(args.z);

            return props;
        }

    }
}
