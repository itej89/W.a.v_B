#pragma once 

#include <stdint-gcc.h>

#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{

    class Payload_Generic_Header_NACK : public PayloadObject
    {

        public:

    void initialize_PayloadItems();

         Payload_Generic_Header_NACK(std::vector<uint8_t> DOIPPayload);
        
        uint8_t GetNAK() ;
    
    };

}