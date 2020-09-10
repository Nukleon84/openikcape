#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "include/thermodynamics.h"

#include "include/activityProperties.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {

        ActivityProperties calculateNRTL(ActivityArguments args, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
             
            auto matrices = sys->binaryparameters.at("NRTL").p;
            auto a = matrices.at("A");
            auto b = matrices.at("B");
            auto c = matrices.at("C");
            auto d = matrices.at("D");
            auto e = matrices.at("E");
            auto f = matrices.at("F");

            auto T = args.T;
            auto P = args.P;
            auto x = args.x;
            auto NC = sys->NC;

            ActivityProperties result;
            result.gamma= VectorXReal(NC);
         

            auto tau = MatrixXReal(NC, NC);
            auto G = MatrixXReal(NC, NC);
            auto S2 = VectorXReal(NC);

            for (int i = 0; i < NC; i++)
            {
                for (int j = 0; j < NC; j++)
                {

                    tau(i, j) = a(i, j) + b(i, j) / T + e(i, j) * log(T) + f(i, j) * T;
                    auto sij=c(i, j) + d(i, j) * (T - 273.15);
                    G(i, j) = exp(- sij * tau(i, j)) ;
                }
            }
                        

            for (int i = 0; i < NC; i++)
            {
                S2[i] = 0.0;
                for (int k = 0; k < NC; k++)
                {
                    S2[i] +=  G(k, i)* x[k] ;
                }
            }

            for (int i = 0; i < NC; i++)
            {
                Real S1 = 0.0;
                for (size_t j = 0; j < NC; j++)
                {
                    S1 += tau(j, i) * G(j, i) * x[j];
                }
                Real S3 = 0.0;

                for (int j = 0; j < NC; j++)
                {
                    Real S5 = 0.0;
                    for (int m = 0; m < NC; m++)
                        S5 += x[m] * tau(m, j) * G(m, j);

                    S3 += x[j] * G(i, j) / S2[j] * (tau(i, j) - S5 / (S2[j]));
                }

    	    	
                result.gamma[i] = exp(S1 / S2[i] + S3);
            }

            Real S6=0.0;
             for (int i = 0; i < NC; i++)
            {
                S6+= args.x[i]*log(result.gamma[i]);
            }

            result.Gex = 8.31433*T*S6;
            result.Hex = 0.0;

            return result;
        }
    } // namespace VLEQFunctions
} // namespace Thermodynamics
  /*
            Expression lnGamma = 0.0;
            Expression S1 = 0.0;
            Expression[] S2 = new Expression[NC];
            Expression S3 = 0.0;
            for (int j = 0; j < NC; j++)
            {
                if (a[j, i] == 0.0 && b[j, i] == 0.0)
                    continue;
                if (c[j, i] == 0.0 && d[j, i] == 0.0)
                    continue;

                S1 += x[j] * tau[j, i] * G[j, i];
            }

            for (int ii = 0; ii < NC; ii++)
            {
                S2[ii] = 0.0;
                for (int k = 0; k < NC; k++)
                {
                    S2[ii] += x[k] * G[k, ii];
                }
            }
            for (int j = 0; j < NC; j++)
            {
                Expression S5 = 0.0;

                for (int m = 0; m < NC; m++)
                {
                    if (a[m, j] == 0.0 && b[m, j] == 0.0)
                        continue;


                    S5 += x[m] * tau[m, j] * G[m, j];
                }

                S3 += x[j] * G[i, j] / Sym.Par(S2[j]) * (tau[i, j] - S5 / Sym.Par(S2[j]));
            }

            lnGamma = S1 / S2[i] + S3;
            _gammaExp = Sym.Exp(lnGamma);

            ValueFunc = () => _gammaExp.Val();
            DiffFunc = (vari) => _gammaExp.Diff(vari);

            this.AddChildren(_gammaExp);
*/