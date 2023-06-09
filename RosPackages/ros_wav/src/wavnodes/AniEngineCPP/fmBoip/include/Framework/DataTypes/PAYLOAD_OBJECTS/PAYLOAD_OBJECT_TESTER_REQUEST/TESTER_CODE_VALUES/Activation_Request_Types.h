#pragma once 

#include <memory>

#include <stdint-gcc.h>
#include <map>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Vehicle_Announce_Further_Actions.h"

 namespace fmBoip
{

class Activation_Request_Types
{   
    public:
    static std::unique_ptr<Activation_Request_Types> Instance;

    enum CODE
    {
        RA_REQ_DEFAULT,
        RA_REQ_WWH_OBD,
        RA_ISO13400_RESERVED,
        RA_REQ_CENTRAL_SECURITY,
        RA_OEM_SPECIFIC,
        DOIPTester_UNKNOWN_CODE
    };
    

    std::map<CODE, uint8_t> CODE_TO_VALUE; 
    
    std::map<uint8_t, CODE> VALUE_TO_CODE; 
    
    std::map<Vehicle_Announce_Further_Actions::CODE, CODE>  FURTHER_ACTION_ROUTING_ACTIVATION;

    Activation_Request_Types();



    CODE DECODE(uint8_t Activation_Request_value) ;
    
    uint8_t Encode(CODE Activation_Request_code);
    
    CODE getRoutingActivationTypeFromVehicleAnnouncementFurtherActions(uint8_t furtheraction) ;

};

}