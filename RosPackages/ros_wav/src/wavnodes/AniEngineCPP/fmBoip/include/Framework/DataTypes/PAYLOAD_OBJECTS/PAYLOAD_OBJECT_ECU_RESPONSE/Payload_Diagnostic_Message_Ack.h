#pragma once 

#include <stdint-gcc.h>
#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{
    class Payload_Diagnostic_Message_Ack : public PayloadObject
    {
        public:

        void initialize_PayloadItems();
        
        Payload_Diagnostic_Message_Ack(std::vector<uint8_t> DOIPPayload);
        
        std::vector<uint8_t>GetSourceAddress();
        
        std::vector<uint8_t> GetTargetAddress();
        
        uint8_t GetAcknowledgement();
        
        std::vector<uint8_t> GetValidationData();
    
    };
}