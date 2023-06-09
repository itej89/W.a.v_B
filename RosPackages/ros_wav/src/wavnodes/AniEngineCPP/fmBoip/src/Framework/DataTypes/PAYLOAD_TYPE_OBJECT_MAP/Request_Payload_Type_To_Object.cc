

#include "Framework/DataTypes/PAYLOAD_TYPE_OBJECT_MAP/Request_Payload_Type_To_Object.h"
\
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Vehicle_Request_EID.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Vehicle_Request_VIN.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Routing_Activation_Requests.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Alive_Check_Response.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Diagnostic_Message.h"


namespace fmBoip
{
         std::shared_ptr<PayloadObject> Request_Payload_Type_To_Object::GetPayloadObjectOfType(Request_Payload_Types::CODE Payload_Type, std::vector<uint8_t> Payload) 
        {
            std::shared_ptr<PayloadObject> payloadObject;
            switch(Payload_Type) {
                case Request_Payload_Types::PLD_VEH_IDEN_REQ:
                    break;
                case Request_Payload_Types::PLD_VEH_IDEN_REQ_EID:
                    payloadObject = std::make_shared<Payload_Vehicle_Request_EID>(Payload);
                    break;
                case Request_Payload_Types::PLD_VEH_IDEN_REQ_VIN:
                    payloadObject = std::make_shared<Payload_Vehicle_Request_VIN>(Payload);
                    break;
                case Request_Payload_Types::PLD_ROUTING_ACTIVATION_REQ:
                    payloadObject = std::make_shared<Payload_Routing_Activation_Requests>( Payload);
                    break;
                case Request_Payload_Types::PLD_ALIVE_CHECK_RES:
                    payloadObject = std::make_shared<Payload_Alive_Check_Response>(Payload);
                    break;
                case Request_Payload_Types::PLD_DOIP_ENTITY_STATUS_REQ:
                    break;
                case Request_Payload_Types::PLD_DIAG_POWER_MODE_REQ:
                    break;
                case Request_Payload_Types::PLD_RESERVED_ISO13400:
                    break;
                case Request_Payload_Types::PLD_DIAG_MESSAGE:
                    payloadObject = std::make_shared<Payload_Diagnostic_Message>(Payload);
                    break;
                case Request_Payload_Types::PLD_MANUFACTURER_SPECIFIC_ACK:
                    break;
                case Request_Payload_Types::DOIPTester_UNKNOWN_CODE:
                    break;
        }
            
            return payloadObject;
            
        }
}