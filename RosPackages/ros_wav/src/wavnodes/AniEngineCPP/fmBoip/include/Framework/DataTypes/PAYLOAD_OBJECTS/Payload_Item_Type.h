#pragma once

#include <stdint-gcc.h>

#include <string>
#include <vector>

namespace fmBoip
{
    class Payload_Item_Type
    {
    public:
      std::vector<uint8_t> RawData;
        int Position = 0;
    uint64_t Length_ISO_13400 = 0;
    bool IsOfVariableLength = false;
    
     Payload_Item_Type(int _Position, uint64_t _Length);
    
     Payload_Item_Type(int _Position);
    
    bool  IsItemLengthNotDefined();

    };
}