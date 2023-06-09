#pragma once

#include <stdint-gcc.h>
#include <vector>
#include <utility>
	


#include "Framework/Validation/DIAGNOSTIC_STATUS.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"
#include "Framework/DOIPLayer/DOIPStateMachines/Interface/IDiagStateForSendRecieve.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/TransportLayer/UDPListen.h"


namespace fmBoip
{
    class VehicleIdentificationDiagState  : public IDiagStateForSendRecieve
    {
        public:

        std::string GetStateID();
        
        int _Init(std::vector<uint8_t> arrDataToBeSent);
        
        std::pair<int, std::vector<uint8_t>> FormatRequest();
    
        std::pair<int, std::vector<uint8_t>> HandleIncomingData(DOIPResponseObject objResponse);

        int SendData(std::vector<uint8_t> data);

    };

}