
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_NAK_Codes.h"

namespace fmBoip
 {
  
  std::shared_ptr<Diagnostic_NAK_Codes> Diagnostic_NAK_Codes::Instance(new Diagnostic_NAK_Codes());

   Diagnostic_NAK_Codes::Diagnostic_NAK_Codes()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, DIAG_NAK_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, DIAG_NAK_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, DIAG_NAK_INVALID_SOURCE_ADDRESS));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x03, DIAG_NAK_UNKOWN_TARGET));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x04, DIAG_NAK_MESSAGE_TOO_LARGE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x05, DIAG_NAK_OUT_OF_MEMORY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x06, DIAG_NAK_TARGET_UNREACHABLE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x07, DIAG_NAK_UNKOWN_NETWORK));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x08, DAIG_NAK_TRANSPORT_PROTOCOL_ERROR));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x09, DIAG_NAK_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, DIAG_NAK_RESERVED_ISO13400));
    }

    
    
    Diagnostic_NAK_Codes::CODE Diagnostic_NAK_Codes::DECODE(uint8_t NAK_Value)
    {

        if(VALUE_TO_CODE.find(NAK_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(NAK_Value);
        }
        else
        {
            return DIAG_NAK_RESERVED_ISO13400;
        }
    }
}