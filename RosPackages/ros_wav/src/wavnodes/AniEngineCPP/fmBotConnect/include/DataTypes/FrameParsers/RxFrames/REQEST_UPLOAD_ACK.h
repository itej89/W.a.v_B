#pragma once


#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class REQEST_UPLOAD_ACK: public RxBaseFrame
    {
        public:
        std::string ID = "";
        ACK::CODE jACK = ACK::NA;
        REQEST_UPLOAD_ACK();
        REQEST_UPLOAD_ACK(std::string _ID, ACK::CODE _ACK);

        void ParseJson(std::string Json);
    };
}