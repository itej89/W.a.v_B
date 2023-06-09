
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Status_Response.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
 {
    
     void Payload_Diagnostic_Status_Response::initialize_PayloadItems()
    { 
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::NODE_TYPE, Payload_Item_Type(0, 1)));
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::MAX_CONCURRENT_TCP_SOCKETS, Payload_Item_Type(1, 1)));
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::CURRENT_OPEN_TCP_SOCKETS, Payload_Item_Type(2, 1)));
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::MAX_DATA_SIZE, Payload_Item_Type(3)));
    }

    
     Payload_Diagnostic_Status_Response::Payload_Diagnostic_Status_Response(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    uint8_t Payload_Diagnostic_Status_Response::GetNodeType() 
    {
        if(Payload.at(NODE_TYPE).RawData.empty() == false)
        {
            return (Payload.at(NODE_TYPE).RawData[0]);
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY, "Payload_Diagnostic_Status_Response:GetNodeType", ""));
            return 0x00;
        }
    }
    
    uint8_t Payload_Diagnostic_Status_Response::GetMaxTCPConnections()
    {
        if(Payload.at(MAX_CONCURRENT_TCP_SOCKETS).RawData.empty() == false)
        {
            return (Payload.at(MAX_CONCURRENT_TCP_SOCKETS).RawData[0]);
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY,  "Payload_Diagnostic_Status_Response:GetMaxTCPConnections",  ""));
            return 0x00;
        }
    }
    
    uint8_t Payload_Diagnostic_Status_Response::GetNumberOfCurrentOpenTCPConnections() 
    {
        if(Payload.at(CURRENT_OPEN_TCP_SOCKETS).RawData.empty() == false)
        {
            return (Payload.at(CURRENT_OPEN_TCP_SOCKETS).RawData[0]);
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::EMPTY,  "Payload_Diagnostic_Status_Response:GetNumberOfCurrentOpenTCPConnections",  ""));
            return 0x00;
        }
    }
    
    std::vector<uint8_t> Payload_Diagnostic_Status_Response::GetMAxDataSize()
    {
        return Payload.at(MAX_DATA_SIZE).RawData;
    }
    
 }