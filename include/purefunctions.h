#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include "include/thermodynamics.h"
using namespace std;

namespace Thermodynamics
{
    namespace PureFunctions
    {
        template <typename T>
        T POLY(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 1)
                throw runtime_error("Too few parameters for Polynom equation");

            auto retval = f.c[0];

            for (int i = 1; i < f.c.size(); i++)
            {
                retval += f.c[i] * pow(temperature, i);
            }

            return retval;
        }

        template <typename T>
        T EPOL(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 1)
                throw runtime_error("Too few parameters for Polynom equation");

            auto retval = f.c[0];

            for (int i = 1; i < f.c.size(); i++)
            {
                retval += f.c[i] * pow(temperature, i);
            }

            return pow(10.0, retval);
        }

        template <typename T>
        T IPOL(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 1)
                throw runtime_error("Too few parameters for Integrated Polynom equation");

            T retval = 0.0;

            for (int i = 0; i < f.c.size(); i++)
            {
                retval += f.c[i] * 1.0 / (i + 1) * pow(temperature, i + 1);
            }

            return retval;
        }

        template <typename T>
        T WATS(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 4)
                throw runtime_error("Too few parameters for Watson equation");
            return f.c[0] * pow(f.c[1] - temperature, f.c[2]) + f.c[3];
        }

        template <typename T>
        T ANTO(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 2)
                throw runtime_error("Too few parameters for Antoine equation");
            return exp(f.c[0] - f.c[1] / (f.c[2] + temperature));
        }

        template <typename T>
        T ANT1(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 7)
                throw runtime_error("Too few parameters for Extended Antoine equation");
            return exp(f.c[0] + f.c[1] / (f.c[2] + temperature) + f.c[3] * temperature + f.c[4] * log(temperature) + f.c[5] * pow(temperature, f.c[6]));
        }

        template <typename T>
        T KIRC(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 3)
                throw runtime_error("Too few parameters for Kirchhoff equation");
            return exp(f.c[0] - f.c[1] / (temperature) + f.c[2] * log(temperature));
        }

        template <typename T>
        T KIR1(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 5)
                throw runtime_error("Too few parameters for Extended Kirchhoff equation");
            return exp(f.c[0] + f.c[1] / (temperature) + f.c[2] * log(temperature) + f.c[3] * pow(temperature, f.c[4]));
        }

        template <typename T>
        T SUTH(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 2)
                throw runtime_error("Too few parameters for Sutherland equation");
            return f.c[0] * sqrt(temperature) / (1 + f.c[1] / temperature);
        }

        template <typename T>
        T WAGN(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 6)
                throw runtime_error("Too few parameters for Wagner equation");
            auto Tr = temperature / f.c[0];
            auto tau = 1 - Tr;

            return exp(log(f.c[1]) + 1.0 / Tr * (f.c[2] * tau + f.c[3] * pow(tau, 1.5) + f.c[4] * pow(tau, 3.0) + f.c[5] * pow(tau, 6.0)));
        }

        template <typename T>
        T CPL(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 5)
                throw runtime_error("Too few parameters for CPL equation");
            return f.c[0] + f.c[1] * temperature + f.c[2] * pow(temperature, 2.0) + f.c[3] * pow(temperature, 3.0) + f.c[4] / pow(temperature, 2.0);
        }

        template <typename T>
        T ICPL(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 6)
                throw runtime_error("Too few parameters for Integrated CPL equation");
            return f.c[0] + f.c[1] * temperature + f.c[2] * pow(temperature, 2.0) + f.c[3] * pow(temperature, 3.0) + f.c[4] * pow(temperature, 4.0) + f.c[5] / temperature;
        }

        template <typename T>
        T VISC(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 2)
                throw runtime_error("Too few parameters for VISC equation");
            return f.c[0] * exp(f.c[1] / temperature) + f.c[2];
        }

        template <typename T>
        T RACK(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 2)
                throw runtime_error("Too few parameters for RACK equation");
            return f.c[0] / (pow(f.c[1], 1 + pow(1 - temperature / f.c[2], f.c[3])));
        }

        template <typename T>
        T ALYL(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 5)
                throw runtime_error("Too few parameters for Aly-Lee equation");
            auto a2T = f.c[2] / temperature;
            auto a4T = f.c[4] / temperature;
            auto p1 = a2T / sinh(a2T);
            auto p2 = a4T / cosh(a4T);
            return f.c[0] + f.c[1] * pow(p1, 2.0) + f.c[3] * pow(p2, 2.0);
        }

        template <typename T>
        T DIP4(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 6)
                throw runtime_error("Too few parameters for DIP4 equation");

            auto Tr = temperature / f.c[0];
            auto h = f.c[2] + f.c[3] * Tr + f.c[4] * pow(Tr, 2.0) + f.c[5] * pow(Tr, 3.0);

            return f.c[1] * pow(1 - Tr, h);
        }

        template <typename T>
        T DIP5(T temperature, const Thermodynamics::Types::PureFunction &f)
        {
            if (f.c.size() < 4)
                throw runtime_error("Too few parameters for DIP5 equation");

            return f.c[0] * pow(temperature, f.c[1]) / (1 + f.c[2] / temperature + f.c[3] / pow(temperature, 2.0));
        }

    } // namespace PureFunctions
} // namespace Thermodynamics