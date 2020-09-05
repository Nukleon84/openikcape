#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
#include "include/thermodynamics.h"
#include "include/substance.h"

using namespace std;

namespace Thermodynamics
{

    namespace Types
    {

        struct ThermodynamicSystem
        {
            std::vector<Substance> substances;
        };
    } // namespace Types
} // namespace Thermodynamics
