#pragma once

#include <string>
#include <map>
#include <memory>
#include <utility>

#include "DataTypes/Enums/ACK.h"
#include "DataTypes/Enums/ANIMSG.h"
#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/FrameParsers/RxFrames/CATEGORY_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/COMMAND_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/REQEST_UPLOAD_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/DATA_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/UPLOAD_END_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/LINK_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/STREAM_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/REQUEST.h"
#include "DataTypes/FrameParsers/RxFrames/BIND.h"
#include "DataTypes/FrameParsers/RxFrames/UNBIND.h"

namespace fmBotConnect
{
    class RxFrameParser
    {
        public:
        std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>> GetBaseFrame(std::string Json);
        
        std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>>  GetRxObject(std::string Json);
    };
}