#pragma once

#include <stdint-gcc.h>
#include<vector>
#include <memory>
#include<map>

namespace fmBoip
{
    class Request_Payload_Types
    {
        public:
        static std::unique_ptr<Request_Payload_Types> Instance;
        
        enum CODE
        {
            PLD_VEH_IDEN_REQ,
            
            PLD_VEH_IDEN_REQ_EID,
            PLD_VEH_IDEN_REQ_VIN,
            
            PLD_ROUTING_ACTIVATION_REQ,
            
            PLD_ALIVE_CHECK_RES,
            
            PLD_DOIP_ENTITY_STATUS_REQ,
            PLD_DIAG_POWER_MODE_REQ,
            PLD_RESERVED_ISO13400,
            
            PLD_DIAG_MESSAGE,
            
            PLD_MANUFACTURER_SPECIFIC_ACK,
            DOIPTester_UNKNOWN_CODE
        };
        
        std::map<CODE, uint16_t> CODE_TO_VALUE;

        Request_Payload_Types();
        
        std::vector<uint8_t> Encode(CODE Paylod_Type);

         std::vector<uint8_t> toBytes(uint32_t Value);
    };

}
