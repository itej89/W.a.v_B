
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"

namespace fmBoip
{

     std::unique_ptr<Response_Payload_Types> Response_Payload_Types::Instance(new Response_Payload_Types()) ;

    Response_Payload_Types::CODE Response_Payload_Types::DECODE(std::vector<uint8_t>  Payload_Type_Value)
    {

        uint16_t Payload_Type = 0;

        for(uint8_t i : Payload_Type_Value)
        {
            Payload_Type <<= 8; 
            Payload_Type |= i;
        }

        if(VALUE_TO_CODE.find(Payload_Type) == VALUE_TO_CODE.end())
            return DOIPTester_UNKNOWN_CODE;
        else
            return VALUE_TO_CODE.at(Payload_Type);
        
    }

    Response_Payload_Types::Response_Payload_Types()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x0000, Response_Payload_Types::PLD_DOIP_HEADER_NAK));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x0004, Response_Payload_Types::PLD_VEH_IDEN_RES));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x0006, Response_Payload_Types::PLD_ROUTING_ACTIVATION_RES));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x0007, Response_Payload_Types::PLD_ALIVE_CHECK_REQ));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x0009, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x4000, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x4002, Response_Payload_Types::PLD_DOIP_ENTITY_STATUS_RES));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x4004, Response_Payload_Types::PLD_DIAG_POWER_MODE_RES));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x4005, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x8000, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x8001, Response_Payload_Types::PLD_DIAG_MESSAGE));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x8002, Response_Payload_Types::PLD_DIAG_MESSAGE_POSITIVE_ACK));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x8003, Response_Payload_Types::PLD_DIAG_MESSAGE_NEGATIVE_ACK));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0x8004, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0xEFFF, Response_Payload_Types::PLD_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0xF000, Response_Payload_Types::PLD_MANUFACTURER_SPECIFIC_ACK));
        VALUE_TO_CODE.insert(std::make_pair<uint16_t, CODE>(0xFFFF, Response_Payload_Types::PLD_MANUFACTURER_SPECIFIC_ACK));

    }
}