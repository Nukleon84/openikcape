#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "include/thermodynamics.h"
#include "include/activityProperties.h"
#include "include/vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;
using namespace autodiff;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {

        Real RachfordRice(Real v, Real T, VectorXReal z, VectorXReal K)
        {
            Real g = 0.0;
            for (size_t i = 0; i < z.size(); i++)
            {
                g += z[i] * (K[i] - 1) / (1.0 - v + v * K[i]);
            }
            return g;
        }

        Real BubblePoint(EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            VectorXReal K = KValues(args, sys);
            Real g = 0.0;
            for (size_t i = 0; i < args.z.size(); i++)
            {
                g += args.z[i] * K[i];
            }
            return g - 1.0;
        }

         Real DewPoint(EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            VectorXReal K = KValues(args, sys);
            Real g = 0.0;
            for (size_t i = 0; i < args.z.size(); i++)
            {
                g += args.z[i] / K[i];
            }
            return g - 1.0;
        }



        Real solveRachfordRice(Real f(Real, Real, VectorXReal, VectorXReal), Real x, Real T, VectorXReal z, VectorXReal K, double tol, int maxiter)
        {
            Real prevX = x;
            for (int i = 0; i < maxiter; i++)
            {
                if (abs(f(x, T, z, K)) < tol)
                    break;
                double dfdx = derivative(f, wrt(x), at(x, T, z, K));
                x = prevX - (f(prevX, T, z, K) / dfdx);
                prevX = x;
            }
            //std::cout << "Iter: " << i << " X: " << x << " f(x): " << f(x, z, K) << endl;
            std::cout << "VF= " << x << endl;
            return x;
        }

        Real solveBubblePointForT(Real f(EquilibriumArguments &, const Thermodynamics::Types::ThermodynamicSystem *), EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys, double tol, int maxiter)
        {
            Real prevX = args.T;

            Real fval = 0.0;
            for (int i = 0; i < maxiter; i++)
            {
                fval = f(args, sys);

                if (abs(fval) < tol)
                    break;

                double dfdx = derivative(f, wrt(args.T), at(args, sys));
                args.T = prevX - (fval / dfdx);
                prevX = args.T;
            }
            //std::cout << "Iter: " << i << " X: " << x << " f(x): " << f(x, z, K) << endl;
            std::cout << "T= " << args.T << endl;
            return args.T;
        }

        EquilibriumProperties calculate_flash_TP(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            EquilibriumProperties props;
            props.T = args.T;
            props.P = args.P;
            props.v = 0.5;
            props.x = VectorXReal(args.x);
            props.y = VectorXReal(args.y);
            props.z = VectorXReal(args.z);

            props.KValues = WilsonKFactors(args, sys);

            auto rrAt0 = RachfordRice(0.0, args.T, args.z, props.KValues);
            auto rrAt1 = RachfordRice(1.0, args.T, args.z, props.KValues);

            if (rrAt0 < 0 && rrAt1 < 0)
            {
                props.v = 0;
                props.phase = PhaseToString[PhaseState::Liquid];
                return props;
            }
            if (rrAt0 > 1 && rrAt1 > 1)
            {
                props.v = 1;
                props.phase = PhaseToString[PhaseState::Vapor];
                return props;
            }
            props.phase = PhaseToString[PhaseState::LiquidVapor];
            props.v = solveRachfordRice(RachfordRice, props.v, args.T, args.z, props.KValues, 1e-5, 20);

            Real denom = 0.0;
            Real vold = props.v;
            for (int j = 0; j < 10; j++)
            {
                props.KValues = KValues(args, sys);
                props.v = solveRachfordRice(RachfordRice, props.v, args.T, args.z, props.KValues, 1e-5, 20);

                for (size_t i = 0; i < args.z.size(); i++)
                {
                    denom = 1.0 - props.v + props.v * props.KValues[i];
                    args.x[i] = args.z[i] / (denom);
                    args.y[i] = props.KValues[i] * args.z[i] / (denom);
                }

                if (abs(vold - props.v) < 1e-4)
                {
                    break;
                }
                else
                    vold = props.v;
            }

            return props;
        }

        EquilibriumProperties calculate_flash_ZP(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
            EquilibriumProperties props;
            props.T = args.T;
            props.P = args.P;
            props.v = args.v;
            props.x = VectorXReal(args.x);
            props.y = VectorXReal(args.y);
            props.z = VectorXReal(args.z);

            props.phase = PhaseToString[PhaseState::LiquidVapor];

            if (args.v == 0.0)
            {
                props.v = 0;
                props.phase = PhaseToString[PhaseState::Liquid];

                props.T = solveBubblePointForT(BubblePoint, args, sys, 1e-5, 20);
                args.T = props.T;

                Real denom = 0.0;
                Real Told = props.T;
                for (int j = 0; j < 10; j++)
                {
                    args.T.val = props.T.val;
                    props.KValues = KValues(args, sys);
                    props.T = solveBubblePointForT(BubblePoint, args, sys, 1e-5, 20);

                    for (size_t i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }

                    if (abs(Told - props.T) < 1e-4)
                    {
                        break;
                    }
                    else
                        Told = props.T;
                }
            }
            if (args.v == 1.0)
            {
                props.v = 1;
                props.phase = PhaseToString[PhaseState::Vapor];

                props.T = solveBubblePointForT(DewPoint, args, sys, 1e-5, 20);
                args.T = props.T;

                Real denom = 0.0;
                Real Told = props.T;
                for (int j = 0; j < 10; j++)
                {
                    args.T.val = props.T.val;
                    props.KValues = KValues(args, sys);
                    props.T = solveBubblePointForT(DewPoint, args, sys, 1e-5, 20);

                    for (size_t i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }
                    if (abs(Told - props.T) < 1e-4)
                    {
                        break;
                    }
                    else
                        Told = props.T;
                }
            }

            return props;
        }

        /*
        static dual solve(dual f( dual), dual x, double tol, int maxiter)
        {
            dual prevX=x;    
            for (int i = 0; i < maxiter; i++)
            {
                cout << "Iter: " << i << " X: " << x << " f(x): " << f(x) << endl;
                if (abs(f(x)) < tol)
                    break;
                double dfdx = derivative(f, wrt(x), at(x));
                x = prevX - (f(prevX) /   dfdx );
                prevX = x;
            }
            return x;
        }

        static dual f(dual x) //x^2 + 2x -1
        {
            return x * (x + 2.0) - 1.0;
        }
        */

    } // namespace VLEQFunctions
} // namespace Thermodynamics
