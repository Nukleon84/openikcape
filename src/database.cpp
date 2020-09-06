#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <algorithm>

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
            cout << "Opening Property database file "<<  this->filename <<" failed." << endl;
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
        }
        std::cout.flush();
        infile.close();
    }

    Substance Database::find_component(std::string name)
    {

        if (std::find(this->component_names.begin(), this->component_names.end(), name) == this->component_names.end())
        {
            Substance comp;
            comp.name = "ERROR";
            comp.identifier = "ERROR";
            return comp;
        }

        Substance comp;
        comp.name = name;
        comp.identifier = name;
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