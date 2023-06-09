
#include "DataTypes/FrameParsers/RxFrames/LINK_ACK.h"

namespace fmBotConnect
{
     LINK_ACK::LINK_ACK(){}
       LINK_ACK::LINK_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::LINK_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void LINK_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}