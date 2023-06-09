
#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"


namespace fmBotConnect
{
    void TxBaseFrame::ParseJson(std::string Json)
    {
        jsonObject jObj =   jsonObject::parse(Json);
        jsonObject strANSTMSG = jObj["ANSTMSG"].get<std::string>();

        ANSTMSG objANSTMSG;

        if(objANSTMSG.STRING_TO_CODE.find(strANSTMSG) != objANSTMSG.STRING_TO_CODE.end())
            jANSTMSG = objANSTMSG.STRING_TO_CODE.at(strANSTMSG);
        else
            jANSTMSG = ANSTMSG::NA;
    }
}