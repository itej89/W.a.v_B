#pragma once


#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class COMMAND_ACK: public RxBaseFrame
    {
        public:
        std::string ID = "";
        ACK::CODE jACK = ACK::NA;
        COMMAND_ACK();
        COMMAND_ACK(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}