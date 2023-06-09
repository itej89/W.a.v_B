#pragma once


#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class UPLOAD_END_ACK: public RxBaseFrame
    {
        public:
        std::string ID = "";
        ACK::CODE jACK = ACK::NA;
        UPLOAD_END_ACK();
        UPLOAD_END_ACK(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}