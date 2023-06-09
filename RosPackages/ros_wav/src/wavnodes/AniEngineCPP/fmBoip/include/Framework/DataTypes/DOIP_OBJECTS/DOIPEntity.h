#pragma once

#include <stdint-gcc.h>
#include <string>
#include <vector>

#include "UUID.h"

namespace fmBoip
{
    class DOIPEntity
    {
        public:
            std::vector<uint8_t> VIN;
            std::vector<uint8_t> EID;
            std::vector<uint8_t> LogicalAddress;
            std::vector<uint8_t> GID;
            uint8_t FurtherActions = 0;
            std::string IPAddress = (new fmCommon::UUID())->stringValue;
            int Port = -1;
            uint8_t ROUTING_ACTIVATION_RESPONSE_CODE = 0;
            bool IsConnected = false;
            bool ISResponded = false;
    };

}