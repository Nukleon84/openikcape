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
            Unit none = Unit("", "Dimensionless", {0, 0, 0, 0, 0, 0, 0, 0});
            Unit m = Unit("m", "Meter", {1, 0, 0, 0, 0, 0, 0, 0});
            Unit kg = Unit("kg", "Kilogram", {0, 1, 0, 0, 0, 0, 0, 0});
            Unit s = Unit("s", "Second", {0, 0, 1, 0, 0, 0, 0, 0});
            Unit K = Unit("K", "Kelvin", {0, 0, 0, 0, 1, 0, 0, 0});
            Unit mol = Unit("mol", "mo", {0, 0, 0, 0, 0, 1, 0, 0});
            Unit kmol = Unit("kmol", "Kilomol", mol, 1e3, 0.0);

            Unit N = Unit("N", "Newton", (kg * m) / (s ^ 2.0));
            Unit J = Unit("J", "Joule", (N * m));

            Unit Pa = Unit("Pa", "Pascal", N / m ^ 2.0);
            Unit kPa = Unit("kPa", "KiloPascal", Pa, 1e3, 0.0);

            Unit W = Unit("W", "Watt", J / s);

            Unit min = Unit("min", "Minute", s, 60.0, 0.0);
            Unit h = Unit("h", "hour", s, 3600.0, 0.0);

            Unit sqm = Unit("sqm", "square-meter", m ^ 2);
            Unit cum = Unit("cum", "cubic-meter", m ^ 3);

            Unit kJ = Unit("kJ", "KiloJoule", J, 1e3, 0.0);
            Unit MJ = Unit("MJ", "MegaJoule", J, 1e6, 0.0);
            Unit GJ = Unit("GJ", "GigaJoule", J, 1e9, 0.0);

            Unit kW = Unit("kW", "KiloWatt", W, 1e3, 0.0);
            Unit MW = Unit("MW", "MegaWatt", W, 1e6, 0.0);
            Unit GW = Unit("GW", "GigaWatt", W, 1e9, 0.0);

        } // namespace SI

        namespace METRIC
        {
            using namespace UOM;
            using namespace SI;

            Unit C = Unit("DEGC", "Celsius", K, 1.0, 273.15);
            Unit bar = Unit("bar", "Bar (absolute)", Pa, 1e5, 0.0);
            Unit mbar = Unit("mbar", "MilliBar (absolute)", Pa, 1e2, 0.0);

            Unit ton = Unit("ton", "ton (metric)", kg, 1e3, 0.0);
            Unit weightPercent = Unit("w-%", "Weight Percent", kg / kg, 1e-2, 0.0);
            Unit molPercent = Unit("mol-%", "Mol Percent", mol / mol, 1e-2, 0.0);
        } // namespace METRIC

        namespace USENG
        {
            using namespace UOM;
            using namespace SI;
            Unit F = Unit("F", "Fahrenheit", K, 1.0 / 1.8, 459.67 / 1.8);
            Unit lb = Unit("lb", "Pound", kg, 1.0/2.20462262,0.0 );
            

            Unit psi = Unit("psia", "Pounds per square inch (absolute)", Pa, 0.0689476e5, 0.0);
            Unit USGallon = Unit("US-Ga", "US-Gallon", cum, 0.00378541, 0.0);
        } // namespace USENG
    }     // namespace UOM
} // namespace Thermodynamics
