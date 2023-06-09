#pragma once

#include <string>
#include <algorithm>

#include "nlohmann/json.hpp"

#include "UUID.h"

#include "DataTypes/Enums/ANSTMSG.h"



using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class TxBaseFrame
    {
        public:
        bool IsWaitForAck = false;
        std::string FRAME_ID = fmCommon::UUID().stringValue;
        ANSTMSG::CODE jANSTMSG;
    
        void ParseJson(std::string Json);

    };
}