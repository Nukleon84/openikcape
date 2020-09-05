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
            Unit none = Unit(L"", L"Dimensionless", {0, 0, 0, 0, 0, 0, 0, 0});
            Unit m = Unit(L"m", L"Meter", {1, 0, 0, 0, 0, 0, 0, 0});
            Unit kg = Unit(L"kg", L"Kilogram", {0, 1, 0, 0, 0, 0, 0, 0});
            Unit s = Unit(L"s", L"Second", {0, 0, 1, 0, 0, 0, 0, 0});
            Unit K = Unit(L"K", L"Kelvin", {0, 0, 0, 0, 1, 0, 0, 0});
            Unit mol = Unit(L"mol", L"mol", {0, 0, 0, 0, 0, 1, 0, 0});
            Unit kmol = Unit(L"kmol", L"Kilomol", mol, 1e3, 0.0);

            Unit N = Unit(L"N", L"Newton", (kg * m) / (s ^ 2.0));
            Unit J = Unit(L"J", L"Joule", (N * m));

            Unit Pa = Unit(L"Pa", L"Pascal", N / m ^ 2.0);
            Unit kPa = Unit(L"kPa", L"KiloPascal", Pa, 1e3, 0.0);

            Unit W = Unit(L"W", L"Watt", J / s);

            Unit min = Unit(L"min", L"Minute", s, 60.0, 0.0);
            Unit h = Unit(L"h", L"hour", s, 3600.0, 0.0);

            Unit sqm = Unit(L"sqm", L"square-meter", m ^ 2);
            Unit cum = Unit(L"cum", L"cubic-meter", m ^ 3);

            Unit kJ = Unit(L"kJ", L"KiloJoule", J, 1e3, 0.0);
            Unit MJ = Unit(L"MJ", L"MegaJoule", J, 1e6, 0.0);
            Unit GJ = Unit(L"GJ", L"GigaJoule", J, 1e9, 0.0);

            Unit kW = Unit(L"kW", L"KiloWatt", W, 1e3, 0.0);
            Unit MW = Unit(L"MW", L"MegaWatt", W, 1e6, 0.0);
            Unit GW = Unit(L"GW", L"GigaWatt", W, 1e9, 0.0);

        } // namespace SI

        namespace METRIC
        {
        }

    } // namespace UOM
} // namespace Thermodynamics
