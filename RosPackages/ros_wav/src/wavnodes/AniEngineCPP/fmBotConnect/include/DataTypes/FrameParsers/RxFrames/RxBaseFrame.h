#pragma once

#include <string>
#include <algorithm>

#include "nlohmann/json.hpp"

#include "UUID.h"

#include "DataTypes/Enums/ANIMSG.h"



using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class RxBaseFrame
    {
        public:
        std::string FRAME_ID = fmCommon::UUID().stringValue;
        ANIMSG::CODE jANIMSG;
    
       virtual void ParseJson(std::string Json);

    };
}