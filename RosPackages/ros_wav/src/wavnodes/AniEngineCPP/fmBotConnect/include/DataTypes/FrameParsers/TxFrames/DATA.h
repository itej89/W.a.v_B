#pragma once

#include <vector>

#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/Enums/COMMAND_TYPES.h"

using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class DATA: public TxBaseFrame
    {
        public:
        std::string ID = "";
        CATEGORY_TYPES::CODE CATEGORY_TYPE = CATEGORY_TYPES::NA;
        int BLOCK_COUNT = 0;
        std::vector<uint8_t> DATA_BYTES;
        
        DATA(std::string _ID, CATEGORY_TYPES::CODE _TYPE, std::vector<uint8_t> _DATA, int _BLOCK_COUNT);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}