#pragma once 

#include <stdint-gcc.h>
#include <vector>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{

class Payload_Vehicle_Request_VIN : public PayloadObject
{   

    public:
    
    void initialize_PayloadItems();
    
    Payload_Vehicle_Request_VIN();
    
    Payload_Vehicle_Request_VIN(std::vector<uint8_t> DOIPPayload);
    
    void SetVIN(std::vector<uint8_t> VIN);

};

}