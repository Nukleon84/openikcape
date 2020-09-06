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

using namespace std;
using namespace Thermodynamics::Types;
namespace Thermodynamics
{

    void Database::scan_database_file()
    {
        ifstream infile;
        infile.open("prop.dat");
        if (infile.fail())
        { // oops the file did not exist for reading?
            cout << "Input file opening failed." << endl;
            exit(1);
        }

        string line;
        while (getline(infile, line))
        { //read data from file object and put it into string.
            if (line.rfind("SHOR", 0) == 0)
            {
                std::istringstream iss(line);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                 std::istream_iterator<std::string>());
                //cout << results[1]<<" "<< results[2] <<"\n";
                this->componentList.push_back(results[2]);
            }
        }
        std::cout.flush();
        infile.close();
    }

    Substance Database::find_component(std::string name)
    {

        if (std::find(this->componentList.begin(), this->componentList.end(), name) == this->componentList.end())
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
        return this->componentList;
    }

} // namespace Thermodynamics