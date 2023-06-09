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
     class KineticsRequestISLEEPROMWrite : public KineticsRequest {
    public:
        int NoOfBytes;
        int Address;
        int Value;

        KineticsRequestISLEEPROMWrite(int noOfBytes, int address, int value);

        KineticsRequestISLEEPROMWrite(string command);

     };
}