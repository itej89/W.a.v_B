
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/NAK_Codes.h"

namespace fmBoip
 {
    
    std::shared_ptr<NAK_Codes> NAK_Codes::Instance(new NAK_Codes());
    
     NAK_Codes::NAK_Codes()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, NAK_INCORRECT_PATTERN));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, NAK_UNKNOWN_PAYLOAD));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, NAK_MESSAGE_TOO_LARGE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x03, NAK_OUT_OF_MEMORY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x04, NAK_INVALID_PAYLOAD_LENGTH));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x05, NAK_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, NAK_RESERVED_ISO13400));
    }

    
    
    NAK_Codes::CODE NAK_Codes::DECODE(uint8_t NAK_Value)
    {

        if(VALUE_TO_CODE.find(NAK_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(NAK_Value);
        }
        else
        {
            return NAK_RESERVED_ISO13400;
        }
    }
}