#pragma once

#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"

#include "DataTypes/Enums/LINK_ANCHORS.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class BIND: public RxBaseFrame
    {
        public:
        std::string ID = "";
        std::map<LINK_ANCHORS::CODE, string> BIND_INFO;

        BIND();
        BIND(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}