
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Routing_Activation_Response.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
 {
    
    void Payload_Routing_Activation_Response::initialize_PayloadItems()
    {   
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::LOGICAL_ADDRESS_TEST_EQUIPMENT, Payload_Item_Type(0, 2)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::LOGICAL_ADDRESS_DOIP_ENTITY, Payload_Item_Type(2, 2)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::ROUTING_ACTIVATION_RESPONSE_CODE, Payload_Item_Type(4, 1)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::ISO_RESERVED, Payload_Item_Type(5, 4)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::OEM_RESERVED, Payload_Item_Type(9)));
    }

    
    Payload_Routing_Activation_Response::Payload_Routing_Activation_Response(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    std::vector<uint8_t>  Payload_Routing_Activation_Response::GetTestEquipmentLogicalAddress()
    {
        return Payload.at(LOGICAL_ADDRESS_TEST_EQUIPMENT).RawData;
    }
    
    std::vector<uint8_t> Payload_Routing_Activation_Response::GetDOIPEntityLogicalAddress()
    {
        return Payload.at(LOGICAL_ADDRESS_DOIP_ENTITY).RawData;
    }
    
    uint8_t Payload_Routing_Activation_Response::GetRoutingActivationResponseCode()
    {
        if((Payload.at(ROUTING_ACTIVATION_RESPONSE_CODE).RawData.empty() == false))
        {
            return (Payload.at(ROUTING_ACTIVATION_RESPONSE_CODE).RawData[0]);
        }
        else
        {
            return 0x00;
        }
    }
    
    std::vector<uint8_t>  Payload_Routing_Activation_Response::GetISOReserved()
    {
        if(Payload.at(ISO_RESERVED).RawData.empty() == false)
        {
            return Payload.at(ISO_RESERVED).RawData;
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "Payload_Routing_Activation_Response:GetISOReserved",  ""));
             return std::vector<uint8_t>();
        }
    }
    
    std::vector<uint8_t>  Payload_Routing_Activation_Response::GetOEMReserved()
    {
        if(Payload.at(OEM_RESERVED).RawData.empty() == false)
        {
            return (Payload.at(OEM_RESERVED).RawData);
        }
        else
        {
            ValidationErrors.add(ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY, "Payload_Routing_Activation_Response:GetOEMReserved",  ""));
            return std::vector<uint8_t>();
        }
    }
    
 }