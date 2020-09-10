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

using namespace std;
using namespace Thermodynamics::Types;

namespace Thermodynamics
{
    namespace Types
    {

        void BinaryParameterSet::set_value(std::string matrix, int i, int j, double value)
        {
             if (i < 0 || i > this->NC)
                return;
            if (j < 0 || j > this->NC)
                return;

            if(this->p.count(matrix)>0)
            {
                this->p.at(matrix)(i,j)=value;
            }
        }
        double BinaryParameterSet::get_value(std::string matrix, int i, int j)
        {
            if (i < 0 || i > this->NC)
                return 0.0;
            if (j < 0 || j > this->NC)
                return 0.0;

            if(this->p.count(matrix)>0)
            {
                return this->p.at(matrix)(i,j);
            }
            return 0.0;
        }
    } // namespace Types
} // namespace Thermodynamics
