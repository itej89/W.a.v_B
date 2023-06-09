#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class Diagnostic_NAK_Codes
{

 public:

  static std::shared_ptr<Diagnostic_NAK_Codes> Instance;
    
     enum CODE
    {
        DIAG_NAK_INVALID_SOURCE_ADDRESS,
         DIAG_NAK_UNKOWN_TARGET,
         DIAG_NAK_MESSAGE_TOO_LARGE,
         DIAG_NAK_OUT_OF_MEMORY,
         DIAG_NAK_TARGET_UNREACHABLE,
         DIAG_NAK_RESERVED_ISO13400,
         DIAG_NAK_UNKOWN_NETWORK,
         DAIG_NAK_TRANSPORT_PROTOCOL_ERROR
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;

    Diagnostic_NAK_Codes();

    CODE DECODE(uint8_t NAK_Value);
};

}