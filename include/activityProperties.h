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
        };

        template <typename Scalar, typename Array>
        struct ActivityArgumentsBase
        {
            Scalar T;
            Scalar P;
            Array x;

            
        };

        using Real = autodiff::dual;
        using VectorXReal = autodiff::VectorXdual;
        using MatrixXReal = autodiff::MatrixXdual;

        using ActivityPropertiesExt = ActivityPropertiesBase<double, std::vector<double>>;

        using ActivityProperties = ActivityPropertiesBase<Real, VectorXReal>;
        using ActivityArguments = ActivityArgumentsBase<Real, VectorXReal>;
    } // namespace Types
} // namespace Thermodynamics
