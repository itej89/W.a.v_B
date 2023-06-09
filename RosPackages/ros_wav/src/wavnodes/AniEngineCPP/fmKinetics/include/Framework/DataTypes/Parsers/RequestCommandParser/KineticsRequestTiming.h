#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "StringX.h"
#include "KineticsRequestForActuator.h"
#include "Framework/DataTypes/MachineCommandHelper.h"


using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{
     class KineticsRequestTiming : public KineticsRequestForActuator {
    public:
        int Timing;

        KineticsRequestTiming(int timing, Actuator::etype actuatorType);

        KineticsRequestTiming(string command);

     };
}