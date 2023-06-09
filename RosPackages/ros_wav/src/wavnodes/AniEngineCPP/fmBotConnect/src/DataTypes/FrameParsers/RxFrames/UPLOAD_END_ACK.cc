
#include "DataTypes/FrameParsers/RxFrames/UPLOAD_END_ACK.h"

namespace fmBotConnect
{
     UPLOAD_END_ACK::UPLOAD_END_ACK(){}
       UPLOAD_END_ACK::UPLOAD_END_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::UPLOAD_END_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void UPLOAD_END_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}