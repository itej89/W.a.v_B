
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Message_Nack.h"


namespace fmBoip
 {
void Payload_Diagnostic_Message_Nack::initialize_PayloadItems()
    {
              Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::SOURCE_ADDRESS, Payload_Item_Type(0, 2)));
              Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::TARGET_ADDRESS, Payload_Item_Type(2, 2)));
              Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::NACK, Payload_Item_Type(4, 1)));
              Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::PREVIOUS_DIAGNOSTIC_DATA, Payload_Item_Type(5)));
    }
    
     Payload_Diagnostic_Message_Nack::Payload_Diagnostic_Message_Nack(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    std::vector<uint8_t>  Payload_Diagnostic_Message_Nack::GetSourceAddress()
    {
        return (Payload.at(SOURCE_ADDRESS).RawData);
    }
    
    std::vector<uint8_t>  Payload_Diagnostic_Message_Nack::GetTargetAddress()
    {
        return (Payload.at(TARGET_ADDRESS).RawData);
    }
    
    uint8_t Payload_Diagnostic_Message_Nack::GetNAK()
    {
        if(Payload.at(NACK).RawData.empty() == false)
        {
            return ((Payload.at(NACK).RawData[0]));
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY, "Payload_Diagnostic_Message_NAck:GetNAK" ,  ""));
            return 0x00;
        }
    }
    
    std::vector<uint8_t>  Payload_Diagnostic_Message_Nack::GetPreviousDiagnosticMessage()
    {
        if(Payload.at(PREVIOUS_DIAGNOSTIC_DATA).RawData.empty() == false)
        {
            return Payload.at(PREVIOUS_DIAGNOSTIC_DATA).RawData;
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::NO_PREVIOUS_DIAGNOSTIC_DATA,  "Payload_Diagnostic_Message_NAck:GetPreviousDiagnosticMessage" , ""));
            return std::vector<uint8_t>();
        }
    }
 }