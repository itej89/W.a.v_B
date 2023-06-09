#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

  class NAK_Codes
{

 public:

    static std::shared_ptr<NAK_Codes> Instance;
    
     enum CODE
    {
          NAK_INCORRECT_PATTERN,
         NAK_UNKNOWN_PAYLOAD,
         NAK_MESSAGE_TOO_LARGE,
         NAK_OUT_OF_MEMORY,
         NAK_INVALID_PAYLOAD_LENGTH,
         NAK_RESERVED_ISO13400
    };
    
    std::map<uint8_t, CODE> VALUE_TO_CODE;

    NAK_Codes();
    
    CODE DECODE(uint8_t NAK_Value);
};

}