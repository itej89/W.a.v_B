#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class DOIP_Status_Node_Type
{

 public:

    static std::shared_ptr<DOIP_Status_Node_Type> Instance;
    
     enum CODE
    {
           DOIP_STATUS_DOIP_GATEWAY,
         DOIP_STATUS_DOIP_NODE,
         DOIP_STATUS_RESERVED_ISO13400
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;


    DOIP_Status_Node_Type();

    CODE DECODE(uint8_t Status);
};

}