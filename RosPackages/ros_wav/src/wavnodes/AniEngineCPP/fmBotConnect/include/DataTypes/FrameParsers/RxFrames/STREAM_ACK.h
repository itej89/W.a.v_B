#pragma once


#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class STREAM_ACK: public RxBaseFrame
    {
        public:
        std::string ID = "";
        ACK::CODE jACK = ACK::NA;
        STREAM_ACK();
        STREAM_ACK(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}