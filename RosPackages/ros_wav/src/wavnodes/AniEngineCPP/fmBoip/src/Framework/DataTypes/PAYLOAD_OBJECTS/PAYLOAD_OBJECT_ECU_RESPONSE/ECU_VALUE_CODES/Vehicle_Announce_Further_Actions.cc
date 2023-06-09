
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Vehicle_Announce_Further_Actions.h"

namespace fmBoip
 {
    
    std::shared_ptr<Vehicle_Announce_Further_Actions> Vehicle_Announce_Further_Actions::Instance(new Vehicle_Announce_Further_Actions());
    
     Vehicle_Announce_Further_Actions::Vehicle_Announce_Further_Actions()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, NO_FURTHER_ACTION_REQD));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x0F, RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x10, ROUTING_REQD_CENTRAL_SECURITY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x11, OEM_SPECIFIC));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, OEM_SPECIFIC));
    }

    
    
    Vehicle_Announce_Further_Actions::CODE Vehicle_Announce_Further_Actions::DECODE(uint8_t FurtherActions_Value)
    {
        if(VALUE_TO_CODE.find(FurtherActions_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(FurtherActions_Value);
        }
        else
        {
            return OEM_SPECIFIC;
        }
    }
}