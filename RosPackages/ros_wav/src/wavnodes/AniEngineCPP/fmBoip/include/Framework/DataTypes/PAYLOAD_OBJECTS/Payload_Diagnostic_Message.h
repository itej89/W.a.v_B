#pragma once

#include <stdint-gcc.h>
#include <string>
#include <vector>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

namespace fmBoip
{

 class Payload_Diagnostic_Message: public PayloadObject
{
     public:
      void initialize_PayloadItems();
    
     Payload_Diagnostic_Message(std::vector<uint8_t> DOIPPayload);
    
    Payload_Diagnostic_Message();
    
    std::vector<uint8_t> GetTargetAddress();
    
    std::vector<uint8_t> GetSourceAddress();
    
    std::vector<uint8_t>  GetUserData();
    
    void SetSourceAddress(std::vector<uint8_t> &SA);
    
    void SetTArgetAddress(std::vector<uint8_t> &TA);
    
    void SetUserData(std::vector<uint8_t>&  User_Data);
};

}