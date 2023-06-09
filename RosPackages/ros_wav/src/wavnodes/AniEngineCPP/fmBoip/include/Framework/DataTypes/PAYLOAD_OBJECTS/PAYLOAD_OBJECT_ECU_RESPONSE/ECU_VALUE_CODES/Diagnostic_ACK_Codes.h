#pragma once 

#include <stdint-gcc.h>
#include <map>
#include <memory>

 namespace fmBoip
{

      class Diagnostic_ACK_Codes
      {

      public:

  static std::shared_ptr<Diagnostic_ACK_Codes> Instance;
          
          enum CODE
          {
              DIAG_ACK_PASS,
              DIAG_ACK_RESERVED_ISO13400
          };
          
          std::map<uint8_t, CODE> VALUE_TO_CODE;

          Diagnostic_ACK_Codes();
          
          CODE DECODE(uint8_t ACK_Value);
      };

}