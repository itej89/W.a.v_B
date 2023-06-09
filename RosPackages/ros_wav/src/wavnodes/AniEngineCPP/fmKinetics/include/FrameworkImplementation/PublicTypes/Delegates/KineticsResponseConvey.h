#pragma once

#include <string>
#include <vector> 
#include "../Constants/MachineCommsStates.h"
#include "../Machine.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"
#include "UUID.h"

using std::string;
using std::vector;

using fmCommon::UUID;

namespace fmKinetics
{
    class  KineticsResponseConvey
    {
        public:
            virtual void CommsLost() = 0;

            virtual void MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement) = 0;

            virtual void MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement) = 0;
    };
}