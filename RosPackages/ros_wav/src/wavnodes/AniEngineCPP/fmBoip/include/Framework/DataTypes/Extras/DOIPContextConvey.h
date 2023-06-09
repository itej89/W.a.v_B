#pragma once

#include <stdint-gcc.h>
#include <string>

#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"

namespace fmBoip
{
    class DOIPContextConvey
    {
        public:
            virtual void FoundDOIPEntity(DOIPEntity Entity) = 0;
            virtual void UDSResponseRecieved(std::vector<uint8_t> response) = 0;
    };
}