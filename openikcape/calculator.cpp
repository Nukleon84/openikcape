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

#include "thermodynamics.h"
#include "purefunctions.h"
#include "vleqfunctions.h"

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace Types
    {

        Equilibrium3PropertiesExt Calculator::calc_flash3_tp(double temperature, double pressure, vector<double> z)
        {
            Equilibrium3Arguments args(temperature, pressure, 0.5, z);         
            auto props = Thermodynamics::VLEQFunctions::calculate_flash3_TP(args, this->system);         
            return export_properties3(props);
        }

        EquilibriumPropertiesExt Calculator::calc_flash_tp(double temperature, double pressure, vector<double> z)
        {
            EquilibriumArguments args(temperature, pressure, 0.5, z);           
            auto props = Thermodynamics::VLEQFunctions::calculate_flash_TP(args, this->system);           
            return export_properties(props);
        }

        EquilibriumPropertiesExt Calculator::calc_flash_zp(double vaporfraction, double pressure, vector<double> z)
        {
            EquilibriumArguments args(298.15, pressure, vaporfraction, z);      
            auto props = Thermodynamics::VLEQFunctions::calculate_flash_ZP(args, this->system);
            return export_properties(props);
        }

         EquilibriumPropertiesExt Calculator::calc_flash_zt(double vaporfraction, double temperature, vector<double> z)
        {
            EquilibriumArguments args(temperature, 1.0e5, vaporfraction, z);
            auto props = Thermodynamics::VLEQFunctions::calculate_flash_ZT(args, this->system);
            return export_properties(props);
        }

        ActivityPropertiesExt Calculator::get_vleq_gamma(double temperature, double pressure, vector<double> x)
        {

            auto args = EquilibriumArguments();
            args.T = temperature;
            args.P = pressure;
            auto NC = this->system->NC;
            args.x = VectorXReal(NC);
            args.y = VectorXReal::Zero(NC);
            args.z = VectorXReal::Zero(NC);
            for (size_t i = 0; i < x.size(); i++)
            {
                args.x[i] = x[i];
            }

            auto props = Thermodynamics::VLEQFunctions::ActivityCoefficients(args.T, args.P, args.x, (this->system));

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

                auto prop = Thermodynamics::Types::NameToProperty[property];

                return PureFunctions::get_pure_property(prop, componentIndex, temperature, this->system);
            }
            return 0.0;
        }
    } // namespace Types
} // namespace Thermodynamics
