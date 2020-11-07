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

        Equilibrium3PropertiesExt export_properties3(Equilibrium3Properties props)        
        { 
            auto NC= props.z.size();

            Equilibrium3PropertiesExt result;
            result.T = props.T.val;
            result.P = props.P.val;
            result.vf = props.vf.val;
            result.l1f = props.l1f.val;
            result.l2f = props.l2f.val;
            result.z = std::vector<double>(NC);
            result.x1 = std::vector<double>(NC);
            result.x2 = std::vector<double>(NC);
            result.y = std::vector<double>(NC);
            result.phase = props.phase;
            for (auto i = 0; i < props.z.size(); i++)
            {
                result.z[i] = props.z[i].val;
                result.x1[i] = props.x1[i].val;
                result.x2[i] = props.x2[i].val;
                result.y[i] = props.y[i].val;
            }
            return result;
        }

        EquilibriumPropertiesExt export_properties(EquilibriumProperties props)        
        { 
            auto NC= props.z.size();

            EquilibriumPropertiesExt result;
            result.T = props.T.val;
            result.P = props.P.val;
            result.vf = props.vf.val;
            result.z = std::vector<double>(NC);
            result.x = std::vector<double>(NC);            
            result.y = std::vector<double>(NC);
            result.phase = props.phase;
            for (auto i = 0; i < props.z.size(); i++)
            {
                result.z[i] = props.z[i].val;
                result.x[i] = props.x[i].val;                
                result.y[i] = props.y[i].val;
            }
            return result;
        }
    }
}
