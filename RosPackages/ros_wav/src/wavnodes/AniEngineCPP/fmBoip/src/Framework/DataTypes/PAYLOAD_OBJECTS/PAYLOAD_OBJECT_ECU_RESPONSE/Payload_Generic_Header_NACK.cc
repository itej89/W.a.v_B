
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Generic_Header_NACK.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
 {
    
    void Payload_Generic_Header_NACK::initialize_PayloadItems()
    { 
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::HEADER_NACK, Payload_Item_Type(0, 1)));
    }

         Payload_Generic_Header_NACK::Payload_Generic_Header_NACK(std::vector<uint8_t> DOIPPayload)
        {
            initialize_PayloadItems();
            Decode_Payload(DOIPPayload);
        }
        
        uint8_t Payload_Generic_Header_NACK::GetNAK() 
        {
            if(Payload.at(HEADER_NACK).RawData.empty() == false)
            {
                return (Payload.at(HEADER_NACK).RawData[0]);
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY, "Payload_Generic_Header_NAK:GetNAK",  ""));
                return 0x00;
            }
        }
    
 }