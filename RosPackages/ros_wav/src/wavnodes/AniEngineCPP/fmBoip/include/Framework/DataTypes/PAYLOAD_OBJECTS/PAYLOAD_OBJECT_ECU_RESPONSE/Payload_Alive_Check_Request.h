#pragma once 

#include <stdint-gcc.h>
#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{
    class Payload_Alive_Check_Request : public PayloadObject
    {
        public:
        void initialize_PayloadItems();
    
        Payload_Alive_Check_Request();
    
        Payload_Alive_Check_Request(std::vector<uint8_t> DOIPPayload);
    
        void  SetSourceAddress(std::vector<uint8_t>  SA);
    
    };
}