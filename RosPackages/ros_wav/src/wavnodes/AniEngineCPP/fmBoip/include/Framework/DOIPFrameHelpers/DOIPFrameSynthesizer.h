#pragma once

#include <stdint-gcc.h>

#include <string>
#include <memory>
#include <vector>

#include "Framework/DataTypes/Extras/IPEndPoint.h"
#include "Framework/DataTypes/ADDRESSING_TYPES.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"


namespace fmBoip
 {
    class DOIPFrameSynthesizer {
        public:
             std::vector<uint8_t> CreateDOIPFrame(DOIPRequestObject& DOIPObject);
            DOIPRequestObject FormHeaderForDoIPFrame(Request_Payload_Types::CODE payloadType);
    };
}
