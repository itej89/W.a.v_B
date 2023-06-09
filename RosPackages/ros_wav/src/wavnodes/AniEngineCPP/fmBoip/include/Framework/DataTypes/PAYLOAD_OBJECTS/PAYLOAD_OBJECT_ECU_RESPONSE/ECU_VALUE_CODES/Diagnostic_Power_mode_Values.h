#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class Diagnostic_Power_mode_Values
{

 public:

    static std::shared_ptr<Diagnostic_Power_mode_Values> Instance;
    
     enum CODE
    {
          DIAG_POWER_MODE_NOT_READY,
         DIAG_POWER_MODE_READY,
         DIAG_POWER_MODE_NOT_SUPPORTED,
         DIAG_POWER_MODE_RESERVED_ISO13400
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;


    Diagnostic_Power_mode_Values();

    CODE DECODE(uint8_t Power_Mode);
};

}