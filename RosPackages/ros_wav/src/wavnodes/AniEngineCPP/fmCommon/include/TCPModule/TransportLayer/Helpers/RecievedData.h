#pragma once

#include <stdint-gcc.h>
#include <vector>

#include "TCPModule/DataTypes/Extras/IPEndPoint.h"

namespace fmCommon
 {
    class RecievedData {
        public:
        IPEndPoint RemoteEndPoint;
        std::vector<uint8_t> recvBuffer;

        RecievedData(IPEndPoint _RemoteEndPoint, std::vector<uint8_t> _recvBuffer);
        RecievedData();
    };
}