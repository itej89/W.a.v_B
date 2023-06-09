
#include "DataTypes/FrameParsers/RxFrames/DATA_ACK.h"

namespace fmBotConnect
{
     DATA_ACK::DATA_ACK(){}
       DATA_ACK::DATA_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::DATA_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void DATA_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}