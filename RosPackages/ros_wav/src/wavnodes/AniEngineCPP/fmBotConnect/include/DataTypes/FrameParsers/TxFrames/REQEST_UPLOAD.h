#pragma once

#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class REQEST_UPLOAD: public TxBaseFrame
    {
        public:
        std::string ID = "";
        int CHUNK_COUNT = 0;
        std::string MD5 = "";
        
        REQEST_UPLOAD(std::string _ID, int _CHUNKCount, std::string _MD5);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}