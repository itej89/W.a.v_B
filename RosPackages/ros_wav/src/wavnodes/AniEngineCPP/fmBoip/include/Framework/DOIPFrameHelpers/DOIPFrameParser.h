#pragma once

#include <stdint-gcc.h>
#include <vector>
#include <memory>

#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"
#include "Framework/DataTypes/PAYLOAD_TYPE_OBJECT_MAP/Response_Payload_Type_To_Object.h"


namespace fmBoip
 {
    class DOIPFrameParser
    {
        public:
        bool Parse(std::vector<uint8_t> DOIPFrame, DOIPResponseObject& responseObject);
        
        int GetLengthFromBytes(std::vector<uint8_t> bytes);

    };
 }