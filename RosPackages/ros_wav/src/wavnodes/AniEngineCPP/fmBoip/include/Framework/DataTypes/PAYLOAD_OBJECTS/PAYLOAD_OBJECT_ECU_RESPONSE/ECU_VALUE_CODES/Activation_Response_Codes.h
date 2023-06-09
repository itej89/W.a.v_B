#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class Activation_Response_Codes
{

 public:
  static std::shared_ptr<Activation_Response_Codes> Instance;
    
     enum CODE
    {
         RA_RES_DENIED_UNKNOWN_SOURCE_ADDRESS,
         RA_RES_DENIED_ALL_SUPPORTED_SOCKETS_REGISTERED_AND_ACTIVE,
         RA_RES_DENIED_SOURCE_ADDRESS_MISMATCH,
         RA_RES_DENIED_SOURCE_ADDRESS_ACTIVE_OTHER_PORT,
         RA_RES_DENIED_MISSING_AUTHENTICATION,
         RA_RES_DENIED_REJECTED_CONFIRMATION,
         RA_RES_DENIED_UNSUPPORTED_ACTIVATION_TYPE,
         RA_RES_SUCCESS,
         RA_RES_CONFIRMATION_REQUIRED,
         RA_RES_RESERVED_ISO13400,
         RA_RES_VEHICLE_MANUFACTURER_SPECIFIC
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;

    Activation_Response_Codes();
    
    CODE DECODE(uint8_t Activation_Response_Value);
};

}