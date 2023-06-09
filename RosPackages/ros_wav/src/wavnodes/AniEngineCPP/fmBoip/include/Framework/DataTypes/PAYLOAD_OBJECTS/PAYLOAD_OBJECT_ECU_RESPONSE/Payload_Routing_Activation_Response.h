#pragma once 

#include <stdint-gcc.h>

#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{

    class Payload_Routing_Activation_Response : public PayloadObject
    {

        public:

    void initialize_PayloadItems();

    
    Payload_Routing_Activation_Response(std::vector<uint8_t> DOIPPayload);
    
    std::vector<uint8_t>  GetTestEquipmentLogicalAddress();
    
    std::vector<uint8_t> GetDOIPEntityLogicalAddress();
    
    uint8_t GetRoutingActivationResponseCode();
    
    std::vector<uint8_t>  GetISOReserved();
    
    std::vector<uint8_t>  GetOEMReserved();
    
    };

}