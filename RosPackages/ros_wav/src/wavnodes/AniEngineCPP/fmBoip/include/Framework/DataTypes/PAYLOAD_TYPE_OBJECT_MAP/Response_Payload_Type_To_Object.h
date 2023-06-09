#pragma once

#include <stdint-gcc.h>
#include <vector>

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"


namespace fmBoip
{
     class Response_Payload_Type_To_Object
    {
        public:
         std::shared_ptr<PayloadObject> GetPayloadObjectOfType(Response_Payload_Types::CODE Payload_Type, std::vector<uint8_t> Payload);
    };

}