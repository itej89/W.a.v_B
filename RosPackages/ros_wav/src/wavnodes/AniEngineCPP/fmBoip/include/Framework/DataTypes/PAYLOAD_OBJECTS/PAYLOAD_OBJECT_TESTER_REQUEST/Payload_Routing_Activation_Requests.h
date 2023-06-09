#pragma once 

#include <stdint-gcc.h>
#include <vector>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{
    class Payload_Routing_Activation_Requests : public PayloadObject
    {   
        public:
    void initialize_PayloadItems();
    
    Payload_Routing_Activation_Requests();
    
    Payload_Routing_Activation_Requests(std::vector<uint8_t> DOIPPayload);
    
    void SetSourceAddress(std::vector<uint8_t> SA);
    
    void SetActivationType(uint8_t ActivationType);
    
    void SetISOReserved(std::vector<uint8_t>  Reserved);
    
    void SetOEMReserved(std::vector<uint8_t>  Reserved);
    
    uint64_t TotalNumberOfBytesInPayload();
    
   std::vector<uint8_t>  Make_Payload();

    };
}