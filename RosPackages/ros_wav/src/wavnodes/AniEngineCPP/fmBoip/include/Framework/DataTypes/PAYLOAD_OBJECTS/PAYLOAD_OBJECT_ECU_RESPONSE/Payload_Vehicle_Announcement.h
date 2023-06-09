#pragma once 

#include <stdint-gcc.h>

#include <map>
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

 namespace fmBoip
{

    class Payload_Vehicle_Announcement : public PayloadObject
    {

        public:

            void initialize_PayloadItems();
            
            Payload_Vehicle_Announcement(std::vector<uint8_t> DOIPPayload);
            
            std::vector<uint8_t> GetVIN();
            
            std::vector<uint8_t>  GetlogicalAddress();
            
            std::vector<uint8_t>  GetEID();
            
            std::vector<uint8_t>  GetGID();
            
            uint8_t GetFurtherAction();
            
            uint8_t GetVINGIDSync();
    
    };

}