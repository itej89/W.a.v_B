#pragma once

#include <string>
#include <map>


#include "DataTypes/Enums/ANSTMSG.h"
#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"

namespace fmBotConnect
{
    class UPLOAD_END : public TxBaseFrame
    {
        public:

        std::string ID = "";
        
        UPLOAD_END(std::string _ID);
        
        std::string Json();

        void ParseJson(std::string Json);
    };
}