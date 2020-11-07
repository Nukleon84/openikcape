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

        MatrixXReal phi_ik(Equilibrium3Properties props, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            MatrixXReal phi(sys->NC, 3);
            auto phi_V = VLEQFunctions::FugacityCoefficients(props.T, props.P, props.y, sys);
            auto phi_L1 = VLEQFunctions::ActivityCoefficients(props.T, props.P, props.x1, sys);
            auto phi_L2 = VLEQFunctions::ActivityCoefficients(props.T, props.P, props.x2, sys);

            for (int i = 0; i < sys->NC; i++)
            {
                auto vp = PureFunctions::get_pure_property(PureProperties::VaporPressure, i, props.T, sys);
                phi(i, 0) = phi_V.phi[i] * props.P;
                phi(i, 1) = phi_L1.gamma[i] * vp;
                phi(i, 2) = phi_L2.gamma[i] * vp;
            }
            return phi;
        }

        Real E_i(int i, VectorXReal beta, MatrixXReal phi)
        {
            Real Ei = 0.0;
            for (auto k = 0; k < beta.size(); k++)
            {
                Ei += beta[k] / phi(i, k);
            }
            return Ei;
        }
        Real Q(VectorXReal beta, VectorXReal z, Equilibrium3Properties props, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            Real q = 0;

            for (auto i = 0; i < beta.size(); i++)
            {
                q += beta[i];
            }

            auto phi = phi_ik(props, sys);

            for (auto i = 0; i < z.size(); i++)
            {
                q -= z[i] * log(E_i(i, beta, phi) );
            }

            return q;
        }

        Equilibrium3Properties calculate_flash3_TP(Equilibrium3Arguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            Equilibrium3Properties props;
            props.T = args.T;
            props.P = args.P;
            props.vf = 0.1;
            props.l1f = 0.45;
            props.l2f = 0.45;
            props.x1 = VectorXReal(args.x1);
            props.x2 = VectorXReal(args.x2);
            props.y = VectorXReal(args.y);
            props.z = VectorXReal(args.z);

            props.phase="Vapor-Liquid-Liquid";
            VectorXReal beta=VectorXReal(3);
            beta[0]= props.vf;
            beta[1]= props.l1f;
            beta[2]= props.l2f;
            
            for (int i = 0; i < sys->NC; i++)
            {
                props.x1[i]= sys->substances[i].phaseL1split* props.z[i];
                props.x2[i]= (1-sys->substances[i].phaseL1split)* props.z[i];
            }

            auto phi=phi_ik(props, sys);

            for (int i = 0; i < sys->NC; i++)
            {
                props.y[i]= props.z[i]*beta[0]/(E_i(i,beta,phi)*phi(i,0) ) ;
                props.x1[i]= props.z[i]*beta[1]/(E_i(i,beta,phi)*phi(i,1) ) ;
                props.x2[i]= props.z[i]*beta[2]/(E_i(i,beta,phi)*phi(i,2) ) ;
            }

            Real sumy= props.y.sum();
            Real sumx1 =props.x1.sum();
            Real sumx2= props.x2.sum();

            for (int i = 0; i < sys->NC; i++)
            {
                props.y[i]= props.y[i]/sumy ;
                props.x1[i]= props.x1[i]/sumx1 ;
                props.x2[i]= props.x2[i]/sumx2 ;
            }

            return props;
        }

    } // namespace VLEQFunctions
} // namespace Thermodynamics
