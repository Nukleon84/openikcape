#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <map>

#include "include/uom.h"
using namespace std;

namespace Thermodynamics
{

    namespace Types
    {
#pragma region Enums
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

#pragma endregion

        struct PureFunction
        {
            PureProperties property;
            PureCorrelations correlation;
            std::vector<double> c;
            double tmin, tmax, refx;
            //    xUnit:: uom.Unit
            //  yUnit:: uom.Unit
        };

        extern std::map<PureCorrelations, string> CorrelationToName;
        extern std::map<string, PureCorrelations> NameToCorrelation;
        extern std::map<string, PureProperties> NameToProperty;
        struct Quantity
        {
            std::string symbol;
            std::string name;
            Thermodynamics::UOM::Unit unit;
            double amount;

            Quantity(std::string symbol, std::string name, double amount, Thermodynamics::UOM::Unit baseUnit) : symbol(symbol),
                                                                                                                name(name),
                                                                                                                unit(baseUnit),
                                                                                                                amount(amount)
            {
            }

            double convert_to(Thermodynamics::UOM::Unit otherUnit);
            void assign_value(double value, Thermodynamics::UOM::Unit otherUnit);
        };

        struct Substance
        {
            std::string name;
            std::string casNo;
            std::string identifier;
            std::string formula;
            std::map<MolecularProperties, Quantity> constants;
            std::map<PureProperties, PureFunction> functions;
            bool isInert = false;
        };

        //Forward declaration to break cyclic dependency with Database class
        class ThermodynamicSystem;

        class Database
        {
            std::string filename;
            std::vector<string> component_names;
            std::vector<Substance> known_components;

            void scan_database_file();
            PureFunction parse_function(ifstream &infile, vector<string> &results);

        public:
            Database(std::string file)
            {
                this->filename = file;
                this->scan_database_file();
            };

            Thermodynamics::Types::Substance find_component(std::string name);
            void fill_binary_parameters(Thermodynamics::Types::ThermodynamicSystem *system);
            std::vector<string> get_component_list();
        };

        class ThermodynamicSystem
        {
            
  

        public:
            std::string name;
            ThermodynamicSystem(std::string name, Thermodynamics::Types::Database &db, std::vector<string> componentList)
            {
                this->name = name;

                for (auto name : componentList)
                {
                    auto comp = db.find_component(name);

                    if (comp.identifier != "ERROR")
                    {
                        substances.push_back(comp);
                    }
                }
                db.fill_binary_parameters(this);
            };
            std::vector<Substance> substances;
            std::vector<Substance> get_component_list()
            {
                return this->substances;
            }
        };

        class Calculator
        {
            ThermodynamicSystem *system;

        public:
            Calculator(ThermodynamicSystem &system)
            {
                this->system = &system;
            };

            double get_pure_property(string property, int componentIndex, double temperature);
        };

    } // namespace Types
} // namespace Thermodynamics