#pragma once 

#include <vector>
#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{

    class Payload_Diagnostic_Status_Response : public PayloadObject
    {

        public:

        void initialize_PayloadItems();

    
     Payload_Diagnostic_Status_Response(std::vector<uint8_t> DOIPPayload);
    
    uint8_t GetNodeType();
    
    uint8_t GetMaxTCPConnections();
    
    uint8_t GetNumberOfCurrentOpenTCPConnections();
    
    std::vector<uint8_t> GetMAxDataSize();
};
}