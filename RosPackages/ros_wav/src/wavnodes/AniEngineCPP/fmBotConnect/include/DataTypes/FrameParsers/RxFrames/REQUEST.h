#pragma once

#include <vector>
#include <map>
#include <utility>

#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/Enums/COMMAND_TYPES.h"
#include "DataTypes/Enums/LINK_ANCHORS.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class REQUEST: public RxBaseFrame
    {
        public:
        std::string ID = "";
        std::map<LINK_ANCHORS::CODE, std::string> REQUEST_DATA;
        
        REQUEST();
        REQUEST(std::string _ID,  std::map<LINK_ANCHORS::CODE, std::string> _DATA);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}