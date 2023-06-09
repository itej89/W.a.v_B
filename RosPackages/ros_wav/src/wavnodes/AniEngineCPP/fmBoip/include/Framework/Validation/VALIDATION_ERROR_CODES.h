#pragma once

#include <map>
#include <string>


namespace fmBoip
 {
  

  class VALIDATION_ERROR_CODES{
      public:
      enum eType
      {
        FAIL,
        EMPTY,
        INCORRECT_LENGTH,
        INVALID_DATA,
        NO_PAYLOAD_ITEMS_FOUND,
        NETWORK_DISCONN,
        EMPTY_SOCKET,
        REMOTE_SOCKET_DISCONN,
        REMOTE_SOCKET_REFUSED_CONN,
        NO_PREVIOUS_DIAGNOSTIC_DATA,
        NO_SOURCE_ADDRESS
      };
    
        VALIDATION_ERROR_CODES();
        
        std::map<eType, std::string> enumtostring;     
    };

 }

