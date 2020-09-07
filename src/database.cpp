#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <cctype>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include "include/thermodynamics.h"
#include "include/unitsets.h"

using namespace std;
using namespace Thermodynamics::Types;

using namespace Thermodynamics::UOM::SI;

namespace Thermodynamics
{

    void Database::scan_database_file()
    {
        ifstream infile;
        infile.open(this->filename);
        if (infile.fail())
        { // oops the file did not exist for reading?
            cout << "Opening Property database file " << this->filename << " failed." << endl;
            exit(1);
        }

        string line;
        while (getline(infile, line))
        { //read data from file object and put it into string.
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());

            if (results[0] == "SYST")
            {
                auto maxComp = stoi(results[3]);
                for (int i = 0; i < maxComp; i++)
                {
                    this->known_components.push_back(Substance());
                }
            }
            if (results[0] == "SHOR")
            {
                auto index = stoi(results[1]) - 1;
                this->known_components[index].identifier = results[2];
                this->component_names.push_back(results[2]);
            }
            if (results[0] == "NAME")
            {
                auto index = stoi(results[1]) - 1;
                this->known_components[index].name = results[2];
            }
            if (results[0] == "CASN")
            {
                auto index = stoi(results[1]) - 1;
                this->known_components[index].casNo = results[2];
            }

            if (results[0] == "MOLW")
            {
                auto index = stoi(results[1]) - 1;
                auto value = stod(results[3]);
                this->known_components[index].constants.insert(
                    {MolecularProperties::MolarWeight,
                     Quantity(results[0], results[0], value, kg / kmol)});
            }

            if (results[0] == "PC")
            {
                auto index = stoi(results[1]) - 1;
                auto value = stod(results[3]);
                this->known_components[index].constants.insert(
                    {MolecularProperties::CriticalPressure,
                     Quantity(results[0], results[0], value, Pa)});
            }
            if (results[0] == "TC")
            {
                auto index = stoi(results[1]) - 1;
                auto value = stod(results[3]);
                this->known_components[index].constants.insert(
                    {MolecularProperties::CriticalTemperature,
                     Quantity(results[0], results[0], value, K)});
            }
            if (results[0] == "AC")
            {
                auto index = stoi(results[1]) - 1;
                auto value = stod(results[3]);
                this->known_components[index].constants.insert(
                    {MolecularProperties::AcentricFactor,
                     Quantity(results[0], results[0], value, none)});
            }

            if (results[0] == "VP")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::VaporPressure;
                this->known_components[index].functions.insert(
                    {PureProperties::VaporPressure,
                     function});
            }

            if (results[0] == "CPID")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::IdealGasHeatCapacity;
                this->known_components[index].functions.insert(
                    {PureProperties::IdealGasHeatCapacity,
                     function});
            }
            if (results[0] == "HVAP")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::HeatOfVaporization;
                this->known_components[index].functions.insert(
                    {PureProperties::HeatOfVaporization,
                     function});
            }
            if (results[0] == "DENL")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::LiquidDensity;
                this->known_components[index].functions.insert(
                    {PureProperties::LiquidDensity,
                     function});
            }
            if (results[0] == "ST")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::SurfaceTension;
                this->known_components[index].functions.insert(
                    {PureProperties::SurfaceTension,
                     function});
            }
            if (results[0] == "CL")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::LiquidHeatCapacity;
                this->known_components[index].functions.insert(
                    {PureProperties::LiquidHeatCapacity,
                     function});
            }

            if (results[0] == "KLIQ")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::LiquidHeatConductivity;
                this->known_components[index].functions.insert(
                    {PureProperties::LiquidHeatConductivity,
                     function});
            }
            if (results[0] == "KVAP")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::VaporHeatConductivity;
                this->known_components[index].functions.insert(
                    {PureProperties::VaporHeatConductivity,
                     function});
            }
            if (results[0] == "VISL")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::LiquidViscosity;
                this->known_components[index].functions.insert(
                    {PureProperties::LiquidViscosity,
                     function});
            }
            if (results[0] == "VISV")
            {
                auto index = stoi(results[1]) - 1;
                auto function = this->parse_function(infile, results);
                function.property = PureProperties::VaporViscosity;
                this->known_components[index].functions.insert(
                    {PureProperties::VaporViscosity,
                     function});
            }
        }
        std::cout.flush();
        infile.close();
    }

    PureFunction Database::parse_function(ifstream &infile, vector<string> &results)
    {
        auto function = PureFunction();

        function.tmin = stod(results[5]);
        function.tmax = stod(results[6]);

        string paramline;
        getline(infile, paramline);
        std::istringstream iss2(paramline);
        std::vector<std::string> parameters((std::istream_iterator<std::string>(iss2)), std::istream_iterator<std::string>());

        for (string i : parameters)
            function.c.push_back(stod(i));

        if (Thermodynamics::Types::NameToCorrelation.count(results[3]) > 0)
            function.correlation = Thermodynamics::Types::NameToCorrelation[results[3]];
        else
            function.correlation = Thermodynamics::Types::PureCorrelations::None;

        return function;
    }

    Substance Database::find_component(std::string name)
    {

        for (auto comp : this->known_components)
        {
            if (comp.identifier  == name || comp.name == name)
                return comp;
        }

        Substance comp;
        comp.name = "ERROR";
        comp.identifier = "ERROR";
        return comp;
    }

    void Database::fill_binary_parameters(ThermodynamicSystem *system)
    {
    }

    std::vector<string> Database::get_component_list()
    {
        return this->component_names;
    }

} // namespace Thermodynamics