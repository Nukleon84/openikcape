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

        EquilibriumPropertiesExt Calculator::calc_flash_tp(double temperature, double pressure, vector<double> z)
        {
            EquilibriumArguments args;
            args.T = temperature;
            args.P = pressure;
            args.z = VectorXReal(this->system->NC);
            args.x = VectorXReal(this->system->NC);
            args.y = VectorXReal(this->system->NC);
            for (size_t i = 0; i < z.size(); i++)
            {
                args.z[i] = z[i];
                args.y[i] = z[i];
                args.x[i] = z[i];
            }

            auto props = Thermodynamics::VLEQFunctions::calculate_flash_TP(args, this->system);

            EquilibriumPropertiesExt results;
            results.T = props.T.val;
            results.P = props.P.val;
            results.v = props.v.val;
            results.z = std::vector<double>(this->system->NC);
            results.x = std::vector<double>(this->system->NC);
            results.y = std::vector<double>(this->system->NC);
            results.phase = props.phase;
            for (size_t i = 0; i < z.size(); i++)
            {
                results.z[i] = props.z[i].val;
                results.x[i] = props.x[i].val;
                results.y[i] = props.y[i].val;
            }
            return results;
        }

        EquilibriumPropertiesExt Calculator::calc_flash_zp(double vaporfraction, double pressure, vector<double> z)
        {
            EquilibriumArguments args;
            args.v = vaporfraction;
            args.T=298.15;
            args.P = pressure;
            args.z = VectorXReal(this->system->NC);
            args.x = VectorXReal(this->system->NC);
            args.y = VectorXReal(this->system->NC);
            for (size_t i = 0; i < z.size(); i++)
            {
                args.z[i] = z[i];
                args.y[i] = z[i];
                args.x[i] = z[i];
            }

            auto props = Thermodynamics::VLEQFunctions::calculate_flash_ZP(args, this->system);

            EquilibriumPropertiesExt results;
            results.T = props.T.val;
            results.P = props.P.val;
            results.v = props.v.val;
            results.z = std::vector<double>(this->system->NC);
            results.x = std::vector<double>(this->system->NC);
            results.y = std::vector<double>(this->system->NC);
            results.phase = props.phase;
            for (size_t i = 0; i < z.size(); i++)
            {
                results.z[i] = props.z[i].val;
                results.x[i] = props.x[i].val;
                results.y[i] = props.y[i].val;
            }
            return results;
        }

         EquilibriumPropertiesExt Calculator::calc_flash_zt(double vaporfraction, double temperature, vector<double> z)
        {
            EquilibriumArguments args;
            args.v = vaporfraction;
            args.T= temperature;
            args.P = 0.5e5;
            args.z = VectorXReal(this->system->NC);
            args.x = VectorXReal(this->system->NC);
            args.y = VectorXReal(this->system->NC);
            for (size_t i = 0; i < z.size(); i++)
            {
                args.z[i] = z[i];
                args.y[i] = z[i];
                args.x[i] = z[i];
            }

            auto props = Thermodynamics::VLEQFunctions::calculate_flash_ZT(args, this->system);

            EquilibriumPropertiesExt results;
            results.T = props.T.val;
            results.P = props.P.val;
            results.v = props.v.val;
            results.z = std::vector<double>(this->system->NC);
            results.x = std::vector<double>(this->system->NC);
            results.y = std::vector<double>(this->system->NC);
            results.phase = props.phase;
            for (size_t i = 0; i < z.size(); i++)
            {
                results.z[i] = props.z[i].val;
                results.x[i] = props.x[i].val;
                results.y[i] = props.y[i].val;
            }
            return results;
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

                auto prop = Thermodynamics::Types::NameToProperty[property];

                return PureFunctions::get_pure_property(prop, componentIndex, temperature, this->system);
            }
            return 0.0;
        }
    } // namespace Types
} // namespace Thermodynamics
