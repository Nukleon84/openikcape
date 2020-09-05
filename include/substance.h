#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
#include"include/thermodynamics.h"
#include "include/quantity.h"
using namespace std;

namespace Thermodynamics
{

    namespace Types
    {

        struct Substance
        {
            std::wstring name;
            std::wstring casNo;
            std::wstring identifier;
            std::wstring formula;
            //std::vector<Variable> _constants = new List<Variable>();
            std::map<MolecularProperties, Quantity> constants;
            std::map<PureProperties, PureFunction> functions;
            bool isInert = false;
        };
    } // namespace Types
} // namespace Thermodynamics