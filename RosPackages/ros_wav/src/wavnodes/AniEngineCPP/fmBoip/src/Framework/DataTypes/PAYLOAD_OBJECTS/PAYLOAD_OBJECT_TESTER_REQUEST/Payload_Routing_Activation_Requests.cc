
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Routing_Activation_Requests.h"

namespace fmBoip
 {
   void Payload_Routing_Activation_Requests::initialize_PayloadItems()
    {
         Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::SOURCE_ADDRESS, Payload_Item_Type(0, 2)));
         Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::ACTIVATION_TYPE, Payload_Item_Type(2, 1)));
         Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::ISO_RESERVED, Payload_Item_Type(3, 4)));
         Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::OEM_RESERVED, Payload_Item_Type(7)));
    }
    
    Payload_Routing_Activation_Requests::Payload_Routing_Activation_Requests() {
        initialize_PayloadItems();
    }
    
    Payload_Routing_Activation_Requests::Payload_Routing_Activation_Requests(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    void Payload_Routing_Activation_Requests::SetSourceAddress(std::vector<uint8_t> SA)
    {
            Payload.at(PayloadObject::SOURCE_ADDRESS).RawData.insert(Payload.at(PayloadObject::SOURCE_ADDRESS).RawData.end(),
            SA.begin(), SA.end());
    }
    
    void Payload_Routing_Activation_Requests::SetActivationType(uint8_t ActivationType)
    {  
         Payload.at(PayloadObject::ACTIVATION_TYPE).RawData.push_back(ActivationType);
    }
    
    void Payload_Routing_Activation_Requests::SetISOReserved(std::vector<uint8_t>  Reserved)
    {
        Payload.at(PayloadObject::ISO_RESERVED).RawData.insert(Payload.at(PayloadObject::ISO_RESERVED).RawData.end(),
            Reserved.begin(), Reserved.end());
    }
    
    void Payload_Routing_Activation_Requests::SetOEMReserved(std::vector<uint8_t>  Reserved)
    {
        Payload.at(PayloadObject::OEM_RESERVED).RawData.insert(Payload.at(PayloadObject::OEM_RESERVED).RawData.end(),
            Reserved.begin(), Reserved.end());
    }
    
    uint64_t Payload_Routing_Activation_Requests::TotalNumberOfBytesInPayload() {
        uint64_t ValidData_Length = 0;
        
    for (auto& it : Payload) {
        if(it.second.RawData.size() > 0)
        {
            ValidData_Length = ValidData_Length + it.second.RawData.size();
        }
    }
        return ValidData_Length;
    }
    
   std::vector<uint8_t>  Payload_Routing_Activation_Requests::Make_Payload()
    {
        uint64_t Required_Payload_Length = TotalNumberOfBytesInPayload();
        
        if(Required_Payload_Length != 0)
        {
            if(Payload.at(SOURCE_ADDRESS).RawData.size() > 0)
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::NO_SOURCE_ADDRESS, "Payload_Routing_Activation_Request:Make_Payload",""));
            }
            
            std::vector<uint8_t>  DOIP_Payload(Required_Payload_Length,0);
            
            if(Payload.at(OEM_RESERVED).RawData.size() > 0)
            { 
                DOIP_Payload.erase(DOIP_Payload.begin()+Payload.at(OEM_RESERVED).Position, DOIP_Payload.begin()+Payload.at(OEM_RESERVED).Position+Payload.at(OEM_RESERVED).RawData.size());
                DOIP_Payload.insert(DOIP_Payload.begin()+Payload.at(OEM_RESERVED).Position, Payload.at(OEM_RESERVED).RawData.begin(), Payload.at(OEM_RESERVED).RawData.end());
            }

            DOIP_Payload.erase(DOIP_Payload.begin()+Payload.at(SOURCE_ADDRESS).Position, DOIP_Payload.begin()+Payload.at(SOURCE_ADDRESS).Position+Payload.at(SOURCE_ADDRESS).RawData.size());
            DOIP_Payload.insert(DOIP_Payload.begin()+Payload.at(SOURCE_ADDRESS).Position, Payload.at(SOURCE_ADDRESS).RawData.begin(), Payload.at(SOURCE_ADDRESS).RawData.end());
           
            DOIP_Payload.erase(DOIP_Payload.begin()+Payload.at(ACTIVATION_TYPE).Position, DOIP_Payload.begin()+Payload.at(ACTIVATION_TYPE).Position+Payload.at(ACTIVATION_TYPE).RawData.size());
            DOIP_Payload.insert(DOIP_Payload.begin()+Payload.at(ACTIVATION_TYPE).Position, Payload.at(ACTIVATION_TYPE).RawData.begin(), Payload.at(ACTIVATION_TYPE).RawData.end());
           
            DOIP_Payload.erase(DOIP_Payload.begin()+Payload.at(ISO_RESERVED).Position, DOIP_Payload.begin()+Payload.at(ISO_RESERVED).Position+Payload.at(ISO_RESERVED).RawData.size());
            DOIP_Payload.insert(DOIP_Payload.begin()+Payload.at(ISO_RESERVED).Position, Payload.at(ISO_RESERVED).RawData.begin(), Payload.at(ISO_RESERVED).RawData.end());
           
            return DOIP_Payload;
        }
        
         ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::NO_PAYLOAD_ITEMS_FOUND, "Payload_Routing_Activation_Request:Make_Payload", ""));
        
        return std::vector<uint8_t>();
    }

}