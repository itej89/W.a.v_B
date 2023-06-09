#pragma once

#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/Enums/COMMAND_TYPES.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class COMMAND: public TxBaseFrame
    {
        public:
        std::string ID = "";
        CATEGORY_TYPES::CODE CATEGORY_TYPE = CATEGORY_TYPES::NA;
        COMMAND_TYPES::CODE  COMMAND_TYPE = COMMAND_TYPES::NA;
        
        COMMAND(std::string _ID);
        COMMAND(std::string _ID, CATEGORY_TYPES::CODE  _CATEGORY, COMMAND_TYPES::CODE _COMMAND);
        std::string Json();

        void ParseJson(std::string Json);
    };
}