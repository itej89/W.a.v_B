#pragma once


#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/Enums/ACK.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class REQUEST_ACK: public TxBaseFrame
    {
        public:
        std::string ID = "";
        ACK::CODE jACK = ACK::NA;
        REQUEST_ACK();
        REQUEST_ACK(std::string _ID, ACK::CODE _ACK);

        std::string Json();
        void ParseJson(std::string Json);
    };
}