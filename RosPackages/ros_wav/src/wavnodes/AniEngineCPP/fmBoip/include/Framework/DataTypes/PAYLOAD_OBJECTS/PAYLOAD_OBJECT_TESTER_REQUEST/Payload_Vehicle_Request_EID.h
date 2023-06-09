#pragma once 

#include <stdint-gcc.h>
#include <vector>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{
    class Payload_Vehicle_Request_EID : public PayloadObject
    {   
        public:
        void initialize_PayloadItems();
        
        Payload_Vehicle_Request_EID();
        
        Payload_Vehicle_Request_EID(std::vector<uint8_t> DOIPPayload);
        
        void SetEID(std::vector<uint8_t> EID);
    };
}