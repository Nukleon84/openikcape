#pragma once

#include <string>
#include "include/uom.h"
using namespace std;

namespace Thermodynamics
{
    namespace UOM
    {
        namespace SI
        {
            using namespace UOM;
            extern Unit none;
            extern Unit m ;
            extern Unit kg ;
            extern Unit s ;
            extern Unit K ;
            extern Unit mol ;
            extern Unit kmol ;

            extern Unit N ;
            extern Unit J;

            extern Unit Pa ;
            extern Unit kPa ;

            extern Unit W;

            extern Unit min ;
            extern Unit h ;

            extern Unit sqm ;
            extern Unit cum ;

            extern Unit kJ ;
            extern Unit MJ ;
            extern Unit GJ ;

            extern Unit kW ;
            extern Unit MW ;
            extern Unit GW ;

        } // namespace SI

        namespace METRIC
        {
            using namespace UOM;
            using namespace SI;

            extern Unit C ;
            extern Unit bar;
            extern Unit mbar ;

            extern Unit ton;
            extern Unit weightPercent ;
            extern Unit molPercent;
        } // namespace METRIC

        namespace USENG
        {
            using namespace UOM;
            using namespace SI;
            extern Unit F;
            extern Unit lb;
            

            extern Unit psi ;
            extern Unit USGallon ;
        } // namespace USENG
    }     // namespace UOM
} // namespace Thermodynamics
