#pragma once

#include<string>
#include<vector>
#include<map>

namespace fmBoip
{
    class ADDRESSING_TYPES
    {
        public:
        enum MessageType
        {
            PHYSICAL,
            FUNCTIONAL
        };
    
        enum UDSRequestType
        {
            UDS,
            TESTER_PRESENT
        };
    
     static std::map<std::string, MessageType> ANI_DOIPTesterAddressingTypeMap;

    ADDRESSING_TYPES();
    
    };

}
