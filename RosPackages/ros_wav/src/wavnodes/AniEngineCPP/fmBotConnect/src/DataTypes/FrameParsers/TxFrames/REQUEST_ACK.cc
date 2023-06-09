
#include "DataTypes/FrameParsers/TxFrames/REQUEST_ACK.h"

namespace fmBotConnect
{
     REQUEST_ACK::REQUEST_ACK(){}
       REQUEST_ACK::REQUEST_ACK(std::string _ID, ACK::CODE _ACK) {
            jANSTMSG = ANSTMSG::REQUEST_ACK;
            ID = _ID;
            jACK = _ACK;
        }

          std::string REQUEST_ACK::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            ACK _ACK;

            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::REQUEST_ACK) + "\" , ");

            json = json.append(" \"ACK\" : \"" + _ACK.CODE_TO_STRING.at(jACK) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" ");

            json = json.append("}");

            return json;
        }

        void REQUEST_ACK::ParseJson(std::string Json)
        {
             TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strAck = jObj["ACK"].get<std::string>();
            ACK _ACK;
            jACK = _ACK.STRING_TO_CODE.at(strAck);
        }
}