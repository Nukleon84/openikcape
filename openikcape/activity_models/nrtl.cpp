#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "thermodynamics.h"

#include "activityProperties.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace VLEQFunctions
    {

        ActivityProperties calculateNRTL(Real T, Real p, VectorXReal x, const Thermodynamics::Types::ThermodynamicSystem *sys)
        {
             
            auto matrices = sys->binaryparameters.at("NRTL").p;
            auto a = matrices.at("A");
            auto b = matrices.at("B");
            auto c = matrices.at("C");
            auto d = matrices.at("D");
            auto e = matrices.at("E");
            auto f = matrices.at("F");

            auto NC = sys->NC;

            ActivityProperties result;
            result.gamma= VectorXReal(NC);
            result.lngamma= VectorXReal(NC);
         

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
                for (int j = 0; j < NC; j++)
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

    	    	
                result.lngamma[i] = S1 / S2[i] + S3;
                result.gamma[i] = exp(result.lngamma[i]);
            }

            auto sumxlng=x.dot(result.lngamma);
            result.Gex = 8.31433*T*(sumxlng.val);
            result.Hex = 0.0;

            return result;
        }
    } // namespace VLEQFunctions
} // namespace Thermodynamics
  