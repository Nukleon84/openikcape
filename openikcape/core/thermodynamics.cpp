#include "thermodynamics.h"

namespace Thermodynamics
{

    namespace Types
    {
        std::map<PureCorrelations, string> CorrelationToName = {
            {PureCorrelations::Polynomial, "POLY"},
            {PureCorrelations::Antoine, "ANTO"},
            {PureCorrelations::ExtendedAntoine, "ANT1"},
            {PureCorrelations::AlyLee, "ALYL"},
            {PureCorrelations::PolynonialInExponent, "EPOL"},
            {PureCorrelations::Dippr106, "DIP4"},
            {PureCorrelations::Rackett, "RACK"},
            {PureCorrelations::Wagner, "WAGN"},
            {PureCorrelations::Watson, "WATS"},
            {PureCorrelations::Dippr102, "DIP5"},
            {PureCorrelations::Kirchhoff, "KIRC"},
            {PureCorrelations::ExtendedKirchhoff, "KIR1"},
            {PureCorrelations::Sutherland, "SUTH"},

        };

        std::map<string, PureProperties> NameToProperty = {
            {"VP", PureProperties::VaporPressure},
            {"CL", PureProperties::LiquidHeatCapacity},
            {"CPID", PureProperties::IdealGasHeatCapacity},
            {"HVAP", PureProperties::HeatOfVaporization},
            {"DENL", PureProperties::LiquidDensity},
            {"ST", PureProperties::SurfaceTension},
            {"VISL", PureProperties::LiquidViscosity},
            {"VISV", PureProperties::VaporViscosity},
            {"KLIQ", PureProperties::LiquidHeatConductivity},
            {"KVAP", PureProperties::VaporHeatConductivity},
        };
        
        std::map<string, PureCorrelations> NameToCorrelation = {
            {"POLY", PureCorrelations::Polynomial},
            {"ANTO", PureCorrelations::Antoine},
            {
                "ANT1",
                PureCorrelations::ExtendedAntoine,
            },
            {"ALYL", PureCorrelations::AlyLee},
            {"EPOL", PureCorrelations::PolynonialInExponent},
            {"DIP4", PureCorrelations::Dippr106},
            {"RACK", PureCorrelations::Rackett},
            {"WAGN", PureCorrelations::Wagner},
            {"WATS", PureCorrelations::Watson},
            {"DIP5", PureCorrelations::Dippr102},
            {"KIRC", PureCorrelations::Kirchhoff},
            {"KIR1", PureCorrelations::ExtendedKirchhoff},
            {"SUTH", PureCorrelations::Sutherland},
        };

    std::map<PhaseState, string> PhaseToString={
        {PhaseState::None, "None"},
        {PhaseState::Liquid, "Liquid"},
        {PhaseState::Vapor, "Vapor"},
        {PhaseState::LiquidVapor, "LiquidVapor"},
        {PhaseState::BubblePoint, "BubblePoint"},
        {PhaseState::DewPoint, "DewPoint"},
        {PhaseState::Supercritical, "Supercritical"},
        {PhaseState::Solid, "Solid"},
    };

    } // namespace Types
} // namespace Thermodynamics
