#pragma once

#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"


namespace fmBotConnect
{
    class BotDetails
    {
        public:
        fmBoip::DOIPEntity Name;
        bool IsResponded = false;
        bool IsConnected = false;
    };
}
