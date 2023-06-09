#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class Vehicle_Announce_Further_Actions
{

 public:

    static std::shared_ptr<Vehicle_Announce_Further_Actions> Instance;
    
     enum CODE
    {
         NO_FURTHER_ACTION_REQD,
         RESERVED_ISO13400,
         ROUTING_REQD_CENTRAL_SECURITY,
         OEM_SPECIFIC
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;

    Vehicle_Announce_Further_Actions();

    CODE DECODE(uint8_t FurtherActions_Value);
};

}