#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "StringX.h"
#include "KineticsRequest.h"
#include "Framework/DataTypes/MachineCommandHelper.h"


using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{
     class KineticsRequestEEPROMRead : public KineticsRequest {
    public:
        EEPROMDetails *MemoryLocation;
        int NoOfBytes;
        int Address;

        KineticsRequestEEPROMRead(EEPROMDetails memoryLocation);

        KineticsRequestEEPROMRead(string command);

     };
}