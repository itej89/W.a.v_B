
#include "DataTypes/FrameParsers/RxFrames/STREAM_ACK.h"

namespace fmBotConnect
{
     STREAM_ACK::STREAM_ACK(){}
       STREAM_ACK::STREAM_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::STREAM_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void STREAM_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}