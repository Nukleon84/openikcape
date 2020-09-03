#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>
using namespace std;

namespace Thermodynamics
{

    namespace Types
    {        
        enum class PureCorrelations
        {
            None,
            Antoine,
            ExtendedAntoine,
            AlyLee,
            Polynomial,
            PolynonialInExponent,
            Dippr106,
            Rackett,
            Wagner,
            Watson,
            Dippr117,
            PolynomialIntegrated,
            Dippr102,
            Kirchhoff,
            ExtendedKirchhoff,
            Sutherland,
            Chemsep16,
            Chemsep16Integrated,
            Chemsep101,
            Chemsep102,
            Chemsep106
        };

        enum class PureProperties
        {
            None,
            VaporPressure,
            IdealGasHeatCapacity,
            LiquidHeatCapacity,
            HeatOfVaporization,
            LiquidDensity,
            SurfaceTension,
            LiquidHeatConductivity,
            VaporHeatConductivity,
            LiquidViscosity,
            VaporViscosity
        };

        enum class MolecularProperties
        {
            None,
            MolarWeight,
            CriticalPressure,
            CriticalTemperature,
            CriticalVolume,
            CriticalDensity,
            AcentricFactor,
            UniquacQ,
            UniquacQP,
            UniquacR,
            HeatOfFormation,
            RKSA,
            RKSB
        };

        enum class EquationOfState
        {
            None,
            Ideal,
            RedlichKwong,
            SoaveRedlichKwong,
            PengRobinson
        };

        enum class EquilibriumApproach
        {
            None,
            GammaPhi,
            PhiPhi
        };

        enum class FugacityMethod
        {
            None,
            Ideal,
            RedlichKwong,
            SoaveRedlichKwong,
            PengRobinson
        };

        enum class ActivityMethod
        {
            None,
            Ideal,
            Wilson,
            NRTL,
            UNIQUAC,
            MODUNIQUAC,
            UNIFAC
        };

        enum class ExcessEnthalpyMethod
        {
            None,
            Ideal,
            NRTL,
            UNIQUAC,
            MODUNIFAC
        };

        enum class EnthalpyDepartureMethod
        {
            None,
            Ideal,
            RedlichKwong,
            SoaveRedlichKwong,
            PengRobinson
        };

        enum class AllowedPhases
        {
            None,
            V,
            L,
            VLE,
            LLE,
            VLLE,
            SLE,
            SLLE
        };

        enum class EnthalpyReferencePhase
        {
            None,
            Liquid,
            Vapor
        };

        enum class PhaseState
        {
            None,
            Solid,
            Liquid,
            BubblePoint,
            LiquidVapor,
            DewPoint,
            Vapor,
            Supercritical
        };

        struct PureFunction
        {
            PureProperties property;
            PureCorrelations correlation;
            std::vector<double> c;
            double tmin, tmax, refx;
            //    xUnit:: uom.Unit
            //  yUnit:: uom.Unit
        };

        struct Substance
        {
            std::wstring name;
            std::wstring casNo;
            std::wstring identifier;
            std::wstring formula;
            //std::vector<Variable> _constants = new List<Variable>();
            std::map<PureProperties, PureFunction> functions;
            bool isInert = false;
        };

        struct ThermodynamicSystem
        {
            std::vector<Substance> substances;
        };

        
        extern std::map<PureCorrelations, string> CorrelationToName;
        extern std::map<string, PureCorrelations > NameToCorrelation;


    } // namespace Types


} // namespace Thermodynamics