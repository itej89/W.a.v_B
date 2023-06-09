#pragma once 

#include <stdint-gcc.h>
#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{
    class Payload_Diagnostic_Power_Mode_Response : public PayloadObject
    {
        public:

        void initialize_PayloadItems();
        
         Payload_Diagnostic_Power_Mode_Response(std::vector<uint8_t> DOIPPayload);
        
        uint8_t GetDiagnosticPowerMode();
    };
}