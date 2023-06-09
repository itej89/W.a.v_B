
#include "DataTypes/FrameParsers/RxFrames/COMMAND_ACK.h"

namespace fmBotConnect
{
     COMMAND_ACK::COMMAND_ACK(){}
       COMMAND_ACK::COMMAND_ACK(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::COMMAND_ACK;
            ID = _ID;
            jACK = _ACK;
        }

        void COMMAND_ACK::ParseJson(std::string Json)
        {
             RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}