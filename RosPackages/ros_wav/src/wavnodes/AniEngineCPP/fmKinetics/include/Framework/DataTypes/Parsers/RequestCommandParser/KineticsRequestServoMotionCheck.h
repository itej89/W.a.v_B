#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "StringX.h"
#include "Framework/DataTypes/MachineCommandHelper.h"
#include "KineticsRequestForActuator.h"

using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{

 class KineticsRequestServoMotionCheck : public KineticsRequestForActuator
{
   public:
    

     KineticsRequestServoMotionCheck(Actuator::etype actuatorType);
    
     KineticsRequestServoMotionCheck(string command);
};

}