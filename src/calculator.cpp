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
            for (size_t i = 0; i < x.size(); i++)
            {
                args.x[i] = x[i];
            }

            auto props = Thermodynamics::VLEQFunctions::ActivityCoefficients(args, (this->system));

            ActivityPropertiesExt results;
            results.Gex = props.Gex.val;
            results.gamma = std::vector<double>(NC);
            results.lngamma = std::vector<double>(NC);
            for (size_t i = 0; i < x.size(); i++)
            {
                results.gamma[i] = props.gamma[i].val;
                results.lngamma[i] = props.lngamma[i].val;
            }
            return results;
        }
        double Calculator::get_pure_property(string property, int componentIndex, double temperature)
        {
            if (componentIndex >= 0 && componentIndex < (int)(system->substances.size()))
            {
                if (Thermodynamics::Types::NameToProperty.count(property) == 0)
                    return -1;
                
                auto prop= Thermodynamics::Types::NameToProperty[property];
                
                return PureFunctions::get_pure_property(prop, componentIndex, temperature, this->system);
            }
            return 0.0;
        }
    } // namespace Types
} // namespace Thermodynamics
