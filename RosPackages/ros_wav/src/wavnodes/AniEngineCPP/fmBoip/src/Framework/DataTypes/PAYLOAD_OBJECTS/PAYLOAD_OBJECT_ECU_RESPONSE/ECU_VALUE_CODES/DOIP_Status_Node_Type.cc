
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/DOIP_Status_Node_Type.h"

namespace fmBoip
 {
    
    std::shared_ptr<DOIP_Status_Node_Type> DOIP_Status_Node_Type::Instance(new DOIP_Status_Node_Type());
    
    DOIP_Status_Node_Type::DOIP_Status_Node_Type()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x00, DOIP_STATUS_DOIP_GATEWAY));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, DOIP_STATUS_DOIP_NODE));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, DOIP_STATUS_RESERVED_ISO13400));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0xFF, DOIP_STATUS_RESERVED_ISO13400));
    }

    
    
    DOIP_Status_Node_Type::CODE DOIP_Status_Node_Type::DECODE(uint8_t Status)
    {
        if(VALUE_TO_CODE.find(Status) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(Status);
        }
        else
        {
            return DOIP_STATUS_RESERVED_ISO13400;
        }
    }
}