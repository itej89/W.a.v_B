

#include "Framework/DataTypes/PAYLOAD_TYPE_OBJECT_MAP/Response_Payload_Type_To_Object.h"


#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Vehicle_Announcement.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Routing_Activation_Response.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Status_Response.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Power_Mode_Response.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Generic_Header_NACK.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Message_Ack.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Message_Nack.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Diagnostic_Message.h"



namespace fmBoip
{   
        std::shared_ptr<PayloadObject> Response_Payload_Type_To_Object::GetPayloadObjectOfType(Response_Payload_Types::CODE Payload_Type, std::vector<uint8_t> Payload) 
        {
            std::shared_ptr<PayloadObject> payloadObject;
            switch(Payload_Type) {
            case Response_Payload_Types::PLD_VEH_IDEN_RES:
                payloadObject = std::make_shared<Payload_Vehicle_Announcement>(Payload);
                break;
            case Response_Payload_Types::PLD_ROUTING_ACTIVATION_RES:
                payloadObject = std::make_shared<Payload_Routing_Activation_Response>(Payload);
                break;
            case Response_Payload_Types::PLD_DOIP_ENTITY_STATUS_RES:
                payloadObject = std::make_shared<Payload_Diagnostic_Status_Response>(Payload);
                break;
            case Response_Payload_Types::PLD_DIAG_POWER_MODE_RES:
                payloadObject = std::make_shared<Payload_Diagnostic_Power_Mode_Response>(Payload);
                break;
            case Response_Payload_Types::PLD_DOIP_HEADER_NAK: 
                payloadObject = std::make_shared<Payload_Generic_Header_NACK>(Payload);
                break;
            case Response_Payload_Types::PLD_DIAG_MESSAGE_POSITIVE_ACK:
                payloadObject = std::make_shared<Payload_Diagnostic_Message_Ack>(Payload);
                break;
            case Response_Payload_Types::PLD_DIAG_MESSAGE_NEGATIVE_ACK:
                payloadObject = std::make_shared<Payload_Diagnostic_Message_Nack>(Payload);
                break;
            case Response_Payload_Types::PLD_DIAG_MESSAGE:
                payloadObject = std::make_shared<Payload_Diagnostic_Message>(Payload);
                break;
            case Response_Payload_Types::PLD_ALIVE_CHECK_REQ:
                break;
            case Response_Payload_Types::PLD_MANUFACTURER_SPECIFIC_ACK:
                break;
            case Response_Payload_Types::PLD_RESERVED_ISO13400:
                break;
            case Response_Payload_Types::DOIPTester_UNKNOWN_CODE:
                break;
            }
            
            if(payloadObject->ValidationErrors.Messages.size() > 0)
            {
                return nullptr;
            }
            else
            {
                return payloadObject;
            }
        }
}