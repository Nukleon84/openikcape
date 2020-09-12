#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>

#include <lib/Eigen/Dense>
#include <lib/autodiff/forward.hpp>
#include <autodiff/forward/eigen.hpp>

#include "include/uom.h"
#include "include/unitsets.h"

using namespace std;

namespace Thermodynamics
{

    namespace Types
    {
        template <typename Scalar, typename Array>
        struct ActivityPropertiesBase
        {
            Scalar Hex;
            Scalar Gex;
            Array gamma;
            Array lngamma;
        };

        template <typename Scalar, typename Array>
        struct ActivityArgumentsBase
        {
            Scalar T;
            Scalar P;
            Array x;
        };

        template <typename Scalar, typename Array>
        struct FugacityPropertiesBase
        {
            Scalar Hex;
            Scalar Gex;
            Array phi;
            Array lnphi;
        };

        template <typename Scalar, typename Array>
        struct FugacityArgumentsBase
        {
            Scalar T;
            Scalar P;
            Array y;
        };

        template <typename Scalar, typename Array>
        struct EquilibriumPropertiesBase
        {
            Scalar T;
            Scalar P;
            Scalar v;
            Array x;
            Array y;
            Array KValues;
        };

        template <typename Scalar, typename Array>
        struct EquilibriumArgumentsBase
        {
            Scalar T;
            Scalar P;
            Scalar v;
            Array x;
            Array y;
        };

        using Real = autodiff::dual;
        using VectorXReal = autodiff::VectorXdual;
        using MatrixXReal = autodiff::MatrixXdual;

        using ActivityPropertiesExt = ActivityPropertiesBase<double, std::vector<double>>;
        using FugacityPropertiesExt = FugacityPropertiesBase<double, std::vector<double>>;
        using EquilibriumPropertiesExt = EquilibriumPropertiesBase<double, std::vector<double>>;

        using ActivityProperties = ActivityPropertiesBase<Real, VectorXReal>;
        using ActivityArguments = ActivityArgumentsBase<Real, VectorXReal>;

        using FugacityProperties = FugacityPropertiesBase<Real, VectorXReal>;
        using FugacityArguments = FugacityArgumentsBase<Real, VectorXReal>;

        using EquilibriumProperties = EquilibriumPropertiesBase<Real, VectorXReal>;
        using EquilibriumArguments = EquilibriumArgumentsBase<Real, VectorXReal>;

    } // namespace Types
} // namespace Thermodynamics
