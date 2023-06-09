#pragma once


#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"

#include "DataTypes/Enums/LINK_ANCHORS.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class UNBIND: public RxBaseFrame
    {
        public:
        std::string ID = "";
        std::map<LINK_ANCHORS::CODE, string> UNBIND_INFO;

        UNBIND();
        UNBIND(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}