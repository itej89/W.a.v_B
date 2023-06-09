
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_Power_mode_Values.h"

namespace fmBoip
 {
    
    std::shared_ptr<Diagnostic_Power_mode_Values> Diagnostic_Power_mode_Values::Instance(new Diagnostic_Power_mode_Values());
    
   Diagnostic_Power_mode_Values::Diagnostic_Power_mode_Values()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, DIAG_POWER_MODE_NOT_READY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, DIAG_POWER_MODE_READY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, DIAG_POWER_MODE_NOT_SUPPORTED));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x03, DIAG_POWER_MODE_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, DIAG_POWER_MODE_RESERVED_ISO13400));
    }

    
    
    Diagnostic_Power_mode_Values::CODE Diagnostic_Power_mode_Values::DECODE(uint8_t Power_Mode)
    {

        if(VALUE_TO_CODE.find(Power_Mode) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(Power_Mode);
        }
        else
        {
            return DIAG_POWER_MODE_RESERVED_ISO13400;
        }
    }
}