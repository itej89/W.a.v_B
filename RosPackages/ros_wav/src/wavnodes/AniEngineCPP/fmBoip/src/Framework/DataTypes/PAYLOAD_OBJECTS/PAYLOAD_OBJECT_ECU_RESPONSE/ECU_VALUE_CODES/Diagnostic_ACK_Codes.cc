
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_ACK_Codes.h"

namespace fmBoip
 {
    std::shared_ptr<Diagnostic_ACK_Codes> Diagnostic_ACK_Codes::Instance(new Diagnostic_ACK_Codes());
     Diagnostic_ACK_Codes::Diagnostic_ACK_Codes()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, DIAG_ACK_PASS));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, DIAG_ACK_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, DIAG_ACK_RESERVED_ISO13400));
    }

    
    
    Diagnostic_ACK_Codes::CODE Diagnostic_ACK_Codes::DECODE(uint8_t ACK_Value)
    {

        if(VALUE_TO_CODE.find(ACK_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(ACK_Value);
        }
        else
        {
            return DIAG_ACK_RESERVED_ISO13400;
        }
    }
}