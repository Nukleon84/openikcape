#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <cctype>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include "include/thermodynamics.h"
#include "include/purefunctions.h"
#include "include/vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace Types
    {

        ActivityPropertiesExt Calculator::get_vleq_gamma(double temperature, double pressure, vector<double> x)
        {
            
            auto args = ActivityArguments();
            args.T = temperature;
            args.P = pressure;
            auto NC = this->system->NC;
            args.x = VectorXReal(NC);
            for (int i = 0; i < x.size(); i++)
            {
                args.x[i] = x[i];
            }

            auto props = Thermodynamics::VLEQFunctions::ActivityCoefficients(args, (this->system));

            ActivityPropertiesExt results;
            results.Gex=props.Gex.val;
            results.gamma= std::vector<double>(NC);
            for (int i = 0; i < x.size(); i++)
            {
                results.gamma[i]=props.gamma[i].val;
            }
            return results;
        }
        double Calculator::get_pure_property(string property, int componentIndex, double temperature)
        {
            if (componentIndex >= 0 && componentIndex < this->system->substances.size())
            {
                if (Thermodynamics::Types::NameToProperty.count(property) == 0)
                    return -1;

                auto f = this->system->substances[componentIndex].functions[Thermodynamics::Types::NameToProperty[property]];

                switch (f.correlation)
                {
                case Thermodynamics::Types::PureCorrelations::Antoine:
                    return PureFunctions::ANTO(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::ExtendedKirchhoff:
                    return PureFunctions::KIR1(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Polynomial:
                    return PureFunctions::POLY(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Kirchhoff:
                    return PureFunctions::KIRC(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::ExtendedAntoine:
                    return PureFunctions::ANT1(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Wagner:
                    return PureFunctions::WAGN(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Watson:
                    return PureFunctions::WATS(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Rackett:
                    return PureFunctions::RACK(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Sutherland:
                    return PureFunctions::SUTH(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::AlyLee:
                    return PureFunctions::ALYL(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Dippr102:
                    return PureFunctions::DIP5(temperature, f);
                    break;
                case Thermodynamics::Types::PureCorrelations::Dippr106:
                    return PureFunctions::DIP4(temperature, f);
                    break;
                default:
                    return 1e-10;
                    break;
                }
            }
            return 0.0;
        }
    } // namespace Types
} // namespace Thermodynamics
