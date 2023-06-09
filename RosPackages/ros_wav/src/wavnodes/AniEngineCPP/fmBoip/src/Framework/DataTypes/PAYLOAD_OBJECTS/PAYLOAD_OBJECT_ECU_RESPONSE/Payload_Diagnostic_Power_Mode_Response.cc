
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Power_Mode_Response.h"


namespace fmBoip
 {
      void Payload_Diagnostic_Power_Mode_Response::initialize_PayloadItems()
    { 
         Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::DIAGNOSTIC_POWER_MODE, Payload_Item_Type(0, 1)));
    }
    
    Payload_Diagnostic_Power_Mode_Response::Payload_Diagnostic_Power_Mode_Response(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    uint8_t Payload_Diagnostic_Power_Mode_Response::GetDiagnosticPowerMode() 
    {
        if(Payload.at(DIAGNOSTIC_POWER_MODE).RawData.empty() == false)
        {
            return (Payload.at(DIAGNOSTIC_POWER_MODE).RawData[0]);
        }
        else
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY,  "Payload_Diagnostic_Power_Mode_Response:GetDiagnosticPowerMode" , ""));
            return 0x00;
        }
    }
 }