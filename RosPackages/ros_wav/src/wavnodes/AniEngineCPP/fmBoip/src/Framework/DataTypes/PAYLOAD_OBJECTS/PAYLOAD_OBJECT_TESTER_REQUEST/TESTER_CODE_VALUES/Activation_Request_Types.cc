
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/TESTER_CODE_VALUES/Activation_Request_Types.h"

namespace fmBoip
 {
     std::unique_ptr<Activation_Request_Types> Activation_Request_Types::Instance(new Activation_Request_Types());

      Activation_Request_Types::Activation_Request_Types()
    {
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint8_t>(RA_REQ_DEFAULT, 0x00));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint8_t>(RA_REQ_WWH_OBD, 0x01));
        CODE_TO_VALUE.insert(std::make_pair<CODE, uint8_t>(RA_REQ_CENTRAL_SECURITY, 0xE0));

        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, RA_REQ_DEFAULT));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, RA_REQ_WWH_OBD));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, RA_ISO13400_RESERVED));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xDF, RA_ISO13400_RESERVED));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xE0, RA_REQ_CENTRAL_SECURITY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xE1, RA_ISO13400_RESERVED));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, RA_ISO13400_RESERVED));


        FURTHER_ACTION_ROUTING_ACTIVATION.insert(std::make_pair<Vehicle_Announce_Further_Actions::CODE, CODE>
        (Vehicle_Announce_Further_Actions::NO_FURTHER_ACTION_REQD, RA_REQ_DEFAULT));

        FURTHER_ACTION_ROUTING_ACTIVATION.insert(std::make_pair<Vehicle_Announce_Further_Actions::CODE, CODE>
        (Vehicle_Announce_Further_Actions::ROUTING_REQD_CENTRAL_SECURITY, RA_REQ_CENTRAL_SECURITY));
    }



    Activation_Request_Types::CODE Activation_Request_Types::DECODE(uint8_t Activation_Request_value) 
    {
        if(VALUE_TO_CODE.find(Activation_Request_value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(Activation_Request_value);
        }
        else
        {
            return DOIPTester_UNKNOWN_CODE;
        }
    }
    
    uint8_t Activation_Request_Types::Encode(Activation_Request_Types::CODE Activation_Request_code)
    {
        return CODE_TO_VALUE.at(Activation_Request_code);
    }
    
    Activation_Request_Types::CODE Activation_Request_Types::getRoutingActivationTypeFromVehicleAnnouncementFurtherActions(uint8_t furtheraction) 
    {
        Vehicle_Announce_Further_Actions furtherActions;
        
        Vehicle_Announce_Further_Actions::CODE code = furtherActions.DECODE(furtheraction);
        
        return FURTHER_ACTION_ROUTING_ACTIVATION.at(code);
    }
}