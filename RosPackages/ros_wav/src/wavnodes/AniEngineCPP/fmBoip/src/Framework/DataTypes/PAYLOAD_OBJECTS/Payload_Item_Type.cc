
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Item_Type.h"

namespace fmBoip
 {
     Payload_Item_Type::Payload_Item_Type(int _Position, uint64_t _Length)
    {
        Position = _Position;
        Length_ISO_13400 = _Length;
        for(int i=0; i<_Length; i++)
        RawData.push_back(0);
    }
    
     Payload_Item_Type::Payload_Item_Type(int _Position)
    {
        Position = _Position;
        IsOfVariableLength = true;
    }
    
    bool  Payload_Item_Type::IsItemLengthNotDefined()
    {
        return IsOfVariableLength;
    }
}