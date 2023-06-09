#pragma once 

#include <string>
#include <vector>


#include "UUID.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"
#include "FrameworkImplementation/PublicTypes/Constants/MachineCommsStates.h"
#include "FrameworkImplementation/PublicTypes/Constants/MachineRequests.h"
#include "FrameworkImplementation/PublicTypes/Machine.h"

using std::string;
using std::vector;

using fmCommon::UUID;

namespace fmKinetics
{
    class MachineCommsConvey
    {
        public:
            virtual void commsStateChanged(MachineCommsStates::etype State) = 0;
            virtual void newMachineFound(Machine Device) = 0;

            virtual void RecievedRemoteCommand(MachineRequests::etype event) = 0;
            virtual void RecievedResponseData(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement) = 0;
            virtual void KineticsResponseDataTimeout(UUID uuid, vector<std::unique_ptr<KineticsResponse>> artialResponse) = 0;

            virtual void RequestSent(KineticsRequest request) = 0;
            virtual void ParameterTriggerSuccuss() = 0;
    };
}