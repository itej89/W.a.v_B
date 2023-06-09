
#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"


namespace fmBotConnect
{
    void RxBaseFrame::ParseJson(std::string Json)
    {
        jsonObject jObj =   jsonObject::parse(Json);
        FRAME_ID = jObj["FRAME_ID"].get<std::string>();
        std::string strANIMSG = jObj["ANIMSG"].get<std::string>();

        ANIMSG objANIMSG;

        if(objANIMSG.STRING_TO_CODE.find(strANIMSG) != objANIMSG.STRING_TO_CODE.end())
            jANIMSG = objANIMSG.STRING_TO_CODE.at(strANIMSG);
        else
            jANIMSG = ANIMSG::NA;
    }
}