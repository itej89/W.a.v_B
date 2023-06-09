#pragma once


#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"


using jsonObject = nlohmann::json;

namespace fmBotConnect
{
    class CATEGORY: public TxBaseFrame
    {
        public:
        std::string ID = "";
        CATEGORY_TYPES::CODE TYPE = CATEGORY_TYPES::NA;
   
        CATEGORY(std::string _ID);
        CATEGORY(std::string _ID, CATEGORY_TYPES::CODE _CODE);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}