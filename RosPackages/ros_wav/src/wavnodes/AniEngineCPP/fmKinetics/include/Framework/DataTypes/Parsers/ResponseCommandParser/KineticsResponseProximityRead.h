#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "Framework/DataTypes/Constants/KineticsResponseAcknowledgement.h"
#include "Framework/DataTypes/Constants/ProximityStateSymbols.h"
#include "StringX.h"
#include "Framework/DataTypes/Constants/KineticsResponseAcknowledgement.h"
#include "KineticsResponse.h"

using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{
     class KineticsResponseProximityRead : public KineticsResponse
    {
        public:
            Actuator::etype ActuatorType;
            ProximityStateSymbols::etype MountState;
            KineticsResponseAcknowledgement::etype ResponseErrorCondition;

            KineticsResponseProximityRead(string response) ;
        
    };

}