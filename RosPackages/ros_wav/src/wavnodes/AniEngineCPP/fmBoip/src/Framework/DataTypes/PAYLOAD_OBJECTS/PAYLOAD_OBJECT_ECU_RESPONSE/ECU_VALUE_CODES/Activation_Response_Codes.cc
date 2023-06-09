
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Activation_Response_Codes.h"

namespace fmBoip
 {
    std::shared_ptr<Activation_Response_Codes> Activation_Response_Codes::Instance(new Activation_Response_Codes());

    Activation_Response_Codes::Activation_Response_Codes()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, RA_RES_DENIED_UNKNOWN_SOURCE_ADDRESS));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, RA_RES_DENIED_ALL_SUPPORTED_SOCKETS_REGISTERED_AND_ACTIVE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, RA_RES_DENIED_SOURCE_ADDRESS_MISMATCH));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x03, RA_RES_DENIED_SOURCE_ADDRESS_ACTIVE_OTHER_PORT));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x04, RA_RES_DENIED_MISSING_AUTHENTICATION));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x05, RA_RES_DENIED_REJECTED_CONFIRMATION));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x06, RA_RES_DENIED_UNSUPPORTED_ACTIVATION_TYPE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x07, RA_RES_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x0F, RA_RES_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x10, RA_RES_SUCCESS));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x11, RA_RES_CONFIRMATION_REQUIRED));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x12, RA_RES_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xDF, RA_RES_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xE0, RA_RES_VEHICLE_MANUFACTURER_SPECIFIC));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFE, RA_RES_VEHICLE_MANUFACTURER_SPECIFIC));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, RA_RES_RESERVED_ISO13400));
    }
    
    Activation_Response_Codes::CODE Activation_Response_Codes::DECODE(uint8_t Activation_Response_Value)
    {
        if(VALUE_TO_CODE.find(Activation_Response_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(Activation_Response_Value);
        }
        else
        {
            return RA_RES_RESERVED_ISO13400;
        }
    }
}