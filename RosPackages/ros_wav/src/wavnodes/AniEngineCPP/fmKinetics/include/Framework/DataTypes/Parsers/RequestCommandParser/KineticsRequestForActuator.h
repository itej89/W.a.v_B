#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "StringX.h"
#include "KineticsRequest.h"

using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{

 class KineticsRequestForActuator : public KineticsRequest
{
   public:
    Actuator::etype ActuatorType;
    
     KineticsRequestForActuator(CommandLabels::CommandTypes::etype requestType);
};

}