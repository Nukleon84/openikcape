#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
using namespace std;

namespace Thermodynamics
{
    namespace UOM
    {
        class Unit
        {
        public:
            std::string symbol;
            std::string name;
            std::array<double, 8> dimensions = {0, 0, 0, 0, 0, 0, 0, 0};
            double factor;
            double offset;

             double get_conversion_factor(Unit other);
             double convert_value(double value, Unit target);

            Unit(std::string symbol, std::string name, std::array<double, 8> dimensions, double factor, double offset)
            { // Constructor
                this->name = name;
                this->symbol = symbol;
                this->dimensions = dimensions;
                this->factor = factor;
                this->offset = offset;
            }

            Unit(std::string symbol, std::string name, Unit baseUnit, double factor, double offset)
            { // Constructor
                this->name = name;
                this->symbol = symbol;
                this->dimensions = baseUnit.dimensions;
                this->factor = factor;
                this->offset = offset;
            }

            Unit(std::string symbol, std::string name, std::array<double, 8> dimensions) : Unit(symbol, name, dimensions, 1.0, 0.0)
            {
            }

            Unit(std::string symbol, std::string name, Unit baseUnit) : Unit(symbol, name, baseUnit, 1.0, 0.0)
            {
            }

            Unit operator*(Unit rhs); 
            Unit operator/(Unit rhs); 
            Unit operator^(double rhs); 

            operator std::string() const ;
        };

    } // namespace UOM
} // namespace Thermodynamics