
#include "DataTypes/FrameParsers/RxFrames/REQEST_UPLOAD_ACK.h"

namespace fmBotConnect
{
     REQEST_UPLOAD_ACK::REQEST_UPLOAD_ACK(){}
       REQEST_UPLOAD_ACK::REQEST_UPLOAD_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::REQEST_UPLOAD_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void REQEST_UPLOAD_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}