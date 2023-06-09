
#include "DataTypes/FrameParsers/TxFrames/UPLOAD_END.h"

namespace fmBotConnect
{
       UPLOAD_END::UPLOAD_END(std::string _ID) {
            jANSTMSG = ANSTMSG::UPLOAD_END;
            ID = _ID;
            IsWaitForAck = true;
        }
        
        std::string UPLOAD_END::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::UPLOAD_END) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");
           
            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void UPLOAD_END::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);
            
            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();
        }
}