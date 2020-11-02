#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>

#include <Eigen/Dense>
#include <autodiff/forward.hpp>
#include <autodiff/forward/eigen.hpp>

#include "uom.h"
#include "thermodynamics.h"

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
            Scalar vf;
            Array z;
            Array x;
            Array y;
            Array KValues;
            string phase;
        };

        template <typename Scalar, typename Array>
        struct Equilibrium3PropertiesBase
        {
            Scalar T;
            Scalar P;
            Scalar vf;
            Scalar l1f;
            Scalar l2f;
            Array z;
            Array x1;
            Array x2;
            Array y;
            Array K1Values;
            Array K2Values;
            string phase;
        };

        template <typename Scalar, typename Array>
        struct EquilibriumArgumentsBase
        {
            Scalar T;
            Scalar P;
            Scalar vf;
            Array z;
            Array x;
            Array y;

            EquilibriumArgumentsBase()
            {

            }
            EquilibriumArgumentsBase(double t, double p, double vf, vector<double> z )
            {
                auto NC=z.size();
                this->T = t;
                this->P = p;
                this->vf = vf;
                this->z = Array(NC);
                this->x = Array(NC);                
                this->y = Array(NC);
                for (size_t i = 0; i < z.size(); i++)
                {
                    this->z[i] = z[i];
                    this->y[i] = z[i];
                    this->x[i] = z[i];                    
                }
            }

        };

         template <typename Scalar, typename Array>
        struct Equilibrium3ArgumentsBase
        {
            Scalar T;
            Scalar P;
            Scalar vf;
            Array z;
            Array x1;
            Array x2;
            Array y;

            Equilibrium3ArgumentsBase(double t, double p, double vf, vector<double> z )
            {
                auto NC=z.size();
                this->T = t;
                this->P = p;
                this->z = Array(NC);
                this->x1 = Array(NC);
                this->x2 = Array(NC);
                this->y = Array(NC);
                for (size_t i = 0; i < z.size(); i++)
                {
                    this->z[i] = z[i];
                    this->y[i] = z[i];
                    this->x1[i] = z[i];
                    this->x2[i] = z[i];
                }
            }
        };


        using Real = autodiff::dual;
        using VectorXReal = autodiff::VectorXdual;
        using MatrixXReal = autodiff::MatrixXdual;

        using ActivityPropertiesExt = ActivityPropertiesBase<double, std::vector<double>>;
        using FugacityPropertiesExt = FugacityPropertiesBase<double, std::vector<double>>;
        using EquilibriumPropertiesExt = EquilibriumPropertiesBase<double, std::vector<double>>;
        using Equilibrium3PropertiesExt = Equilibrium3PropertiesBase<double, std::vector<double>>;

        using ActivityProperties = ActivityPropertiesBase<Real, VectorXReal>;
        using ActivityArguments = ActivityArgumentsBase<Real, VectorXReal>;

        using FugacityProperties = FugacityPropertiesBase<Real, VectorXReal>;
        using FugacityArguments = FugacityArgumentsBase<Real, VectorXReal>;

        using EquilibriumProperties = EquilibriumPropertiesBase<Real, VectorXReal>;
        using EquilibriumArguments = EquilibriumArgumentsBase<Real, VectorXReal>;

        using Equilibrium3Properties = Equilibrium3PropertiesBase<Real, VectorXReal>;
        using Equilibrium3Arguments = Equilibrium3ArgumentsBase<Real, VectorXReal>;


        Equilibrium3PropertiesExt export_properties3(Equilibrium3Properties props);
        EquilibriumPropertiesExt export_properties(EquilibriumProperties props);

    } // namespace Types
} // namespace Thermodynamics
