#pragma once

#include <stdint-gcc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <memory>

#include "Framework/Validation/interface/IValidation.h"


#include "Framework/DataTypes/Extras/IPEndPoint.h"
#include "Framework/TransportLayer/UDPListen.h"

namespace fmBoip
{

    class UDPBroadcast : public IValidation
    {
        public:
        
        static std::unique_ptr<UDPBroadcast> Instance;
        
        void UDPBroadcastPacket(std::vector<uint8_t> Frame);

    };
}