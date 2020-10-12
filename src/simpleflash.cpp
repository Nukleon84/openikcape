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

        Real RachfordRice(EquilibriumArguments &args, const ThermodynamicSystem *sys)
        {
            VectorXReal K = KValues(args, sys);
            Real g = 0.0;
            for (auto i = 0; i < args.z.size(); i++)
            {
                g += args.z[i] * (K[i] - 1) / (1.0 - args.v + args.v * K[i]);
            }
            return g;
        }

        Real BubblePoint(EquilibriumArguments &args, const ThermodynamicSystem *sys)
        {
            VectorXReal K = KValues(args, sys);
            Real g = 0.0;
            for (auto i = 0; i < args.z.size(); i++)
            {
                g += args.z[i] * K[i];
            }
            return g - 1.0;
        }

        Real DewPoint(EquilibriumArguments &args, const ThermodynamicSystem *sys)
        {
            VectorXReal K = KValues(args, sys);
            Real g = 0.0;
            for (auto i = 0; i < args.z.size(); i++)
            {
                g += args.z[i] / K[i];
            }
            return g - 1.0;
        }

        Real solveRachfordRice(Real f(EquilibriumArguments &, const ThermodynamicSystem *), EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys, double tol, int maxiter)
        {
            Real prevX = args.v;
            for (int i = 0; i < maxiter; i++)
            {
                if (abs(f(args, sys)) < tol)
                    break;
                double dfdx = derivative(f, wrt(args.v), at(args, sys));
                args.v = prevX - (f(args, sys) / dfdx);
                prevX = args.v;
            }
            //std::cout << "Iter: " << i << " X: " << x << " f(x): " << f(x, z, K) << endl;
            // std::cout << "VF= " << x << endl;
            return args.v;
        }

        Real solveBubblePointForT(Real f(EquilibriumArguments &, const ThermodynamicSystem *), EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys, double tol, int maxiter)
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
            //std::cout << "T= " << args.T << endl;
            return args.T;
        }

        Real solveBubblePointForP(Real f(EquilibriumArguments &, const Thermodynamics::Types::ThermodynamicSystem *), EquilibriumArguments &args, const Thermodynamics::Types::ThermodynamicSystem *sys, double tol, int maxiter)
        {
            Real prevX = args.P;

            Real fval = 0.0;
            for (int i = 0; i < maxiter; i++)
            {
                fval = f(args, sys);

                if (abs(fval) < tol)
                    break;

                double dfdx = derivative(f, wrt(args.P), at(args, sys));
                args.P = prevX - (fval / dfdx);
                prevX = args.P;
            }
            //std::cout << "Iter: " << i << " X: " << x << " f(x): " << f(x, z, K) << endl;
            //std::cout << "T= " << args.T << endl;
            return args.P;
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

            args.v=0.0;
            auto rrAt0 = RachfordRice(args, sys);
            args.v=1.0;
            auto rrAt1 = RachfordRice(args, sys);

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
            props.v = solveRachfordRice(RachfordRice, args, sys, 1e-6, 20);

            Real denom = 0.0;
            Real vold = props.v;
            for (int j = 0; j < 30; j++)
            {
                props.KValues = KValues(args, sys);
                props.v = solveRachfordRice(RachfordRice, args, sys, 1e-6, 20);

                for (auto i = 0; i < args.z.size(); i++)
                {
                    denom = 1.0 - props.v + props.v * props.KValues[i];
                    args.x[i] = args.z[i] / (denom);
                    args.y[i] = props.KValues[i] * args.z[i] / (denom);
                }

                if (abs(vold - props.v) < 1e-6)
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

                props.T = solveBubblePointForT(BubblePoint, args, sys, 1e-6, 20);
                args.T = props.T;

                Real denom = 0.0;
                Real Told = props.T;
                for (int j = 0; j <30; j++)
                {
                    args.T.val = props.T.val;
                    props.KValues = KValues(args, sys);
                    props.T = solveBubblePointForT(BubblePoint, args, sys, 1e-6, 20);

                    for (auto i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }

                    if (abs(Told - props.T) < 1e-6)
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

                props.T = solveBubblePointForT(DewPoint, args, sys, 1e-6, 20);
                args.T = props.T;

                Real denom = 0.0;
                Real Told = props.T;
                for (int j = 0; j < 30; j++)
                {
                    args.T.val = props.T.val;
                    props.KValues = KValues(args, sys);
                    props.T = solveBubblePointForT(DewPoint, args, sys, 1e-6, 20);

                    for (auto i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }
                    if (abs(Told - props.T) < 1e-6)
                    {
                        break;
                    }
                    else
                        Told = props.T;
                }
            }

            return props;
        }

        EquilibriumProperties calculate_flash_ZT(EquilibriumArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
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

                props.P = solveBubblePointForP(BubblePoint, args, sys, 1e-6, 50);
                args.P = props.P;

                Real denom = 0.0;
                Real Pold = props.P;
                for (int j = 0; j < 30; j++)
                {
                    args.P.val = props.P.val;
                    props.KValues = KValues(args, sys);
                    props.P = solveBubblePointForP(BubblePoint, args, sys, 1e-6, 50);

                    for (auto i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }

                    if (abs(Pold - props.P) < 1e-4)
                    {
                        break;
                    }
                    else
                        Pold = props.P;
                }
            }
            if (args.v == 1.0)
            {
                props.v = 1;
                props.phase = PhaseToString[PhaseState::Vapor];

                props.P = solveBubblePointForP(DewPoint, args, sys, 1e-5, 50);
                args.P = props.P;

                Real denom = 0.0;
                Real Pold = props.P;
                for (int j = 0; j < 30; j++)
                {
                    args.P.val = props.P.val;
                    props.KValues = KValues(args, sys);
                    props.P = solveBubblePointForP(DewPoint, args, sys, 1e-6, 50);

                    for (auto i = 0; i < args.z.size(); i++)
                    {
                        denom = 1.0 - props.v + props.v * props.KValues[i];
                        args.x[i] = args.z[i] / (denom);
                        args.y[i] = props.KValues[i] * args.z[i] / (denom);
                    }
                    if (abs(Pold - props.P) < 1e-6)
                    {
                        break;
                    }
                    else
                        Pold = props.P;
                }
            }

            return props;
        }

    } // namespace VLEQFunctions
} // namespace Thermodynamics
