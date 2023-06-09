

#include "Framework/DataTypes/PAYLOAD_TYPES/Request_Payload_Types.h"

namespace fmBoip
{
    std::unique_ptr<Request_Payload_Types> Request_Payload_Types::Instance(new Request_Payload_Types()) ;

    std::vector<uint8_t> Request_Payload_Types::Encode(CODE Paylod_Type)
    {
        std::vector<uint8_t> EncodedBytes;
        EncodedBytes.push_back((uint8_t)((CODE_TO_VALUE.at(Paylod_Type))&0xFF));
        EncodedBytes.push_back((uint8_t)((CODE_TO_VALUE.at(Paylod_Type) >> 8)&0xFF) );
        return EncodedBytes;
    }

     std::vector<uint8_t> Request_Payload_Types::toBytes(uint32_t Value)
    {
        std::vector<uint8_t> Bytes;
        Bytes.push_back((uint8_t)(Value&0xFF));
        Bytes.push_back((uint8_t)(Value >> 8) &0xFF);
        Bytes.push_back((uint8_t)(Value >> 16) &0xFF);
        Bytes.push_back((uint8_t)(Value >> 24)&0xFF);
        return Bytes;
    }

    Request_Payload_Types::Request_Payload_Types()
    {
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_VEH_IDEN_REQ,0x0001));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_VEH_IDEN_REQ_EID,0x0002));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_VEH_IDEN_REQ_VIN,0x0003));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_ROUTING_ACTIVATION_REQ,0x0005));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_ALIVE_CHECK_RES,0x0008));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0x0009));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0x4000));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_DOIP_ENTITY_STATUS_REQ,0x4001));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_DIAG_POWER_MODE_REQ,0x4003));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0x4005));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0x8000));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_DIAG_MESSAGE,0x8001));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0x8004));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0xEFFF));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0xF000));
        // CODE_TO_VALUE.insert(std::make_pair<CODE, uint16_t>(PLD_RESERVED_ISO13400,0xFFFF));

    }
}
