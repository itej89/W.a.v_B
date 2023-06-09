#pragma once

#include <string>
#include <memory>

#include "TCPModule/TransportLayer/Helpers/RecievedData.h"

namespace fmCommon
{
    class TransportClientConvey
    {
        public:
            virtual void DataRecieved(RecievedData recievedData) = 0;
            virtual void Disconnected() = 0;
            virtual void Timeout(int code) = 0;
    };
}