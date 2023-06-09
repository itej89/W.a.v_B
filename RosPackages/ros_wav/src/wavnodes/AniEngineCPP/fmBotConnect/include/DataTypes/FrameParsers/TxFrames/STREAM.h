#pragma once

#include <vector>
#include <map>
#include <utility>

#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/Enums/COMMAND_TYPES.h"
#include "DataTypes/Enums/LINK_ANCHORS.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class STREAM: public TxBaseFrame
    {
        public:
        std::string ID = "";
        std::map<LINK_ANCHORS::CODE, std::string> STREAM_DATA;
        
        STREAM(std::string _ID,  std::map<LINK_ANCHORS::CODE, std::string> _DATA);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}