#pragma once

#include <stdint-gcc.h>
#include<vector>
#include <memory>
#include<map>

namespace fmBoip
{
    class Response_Payload_Types
    {
        public:
        static std::unique_ptr<Response_Payload_Types> Instance;
        
        enum CODE
        {
            PLD_DOIP_HEADER_NAK,
            PLD_VEH_IDEN_RES,
            PLD_ROUTING_ACTIVATION_RES,
            PLD_ALIVE_CHECK_REQ,
            PLD_DOIP_ENTITY_STATUS_RES,
            PLD_DIAG_POWER_MODE_RES,
            PLD_RESERVED_ISO13400,
            PLD_DIAG_MESSAGE,
            PLD_DIAG_MESSAGE_POSITIVE_ACK,
            PLD_DIAG_MESSAGE_NEGATIVE_ACK,
            PLD_MANUFACTURER_SPECIFIC_ACK,
            DOIPTester_UNKNOWN_CODE
        };
        
        std::map<uint16_t, CODE> VALUE_TO_CODE;

        Response_Payload_Types();
        
        CODE DECODE(std::vector<uint8_t> Payload_Type_Value);

     
    };

}
