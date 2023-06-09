
#include "DataTypes/Enums/ANSTMSG.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/FrameParsers/TxFrames/REQEST_UPLOAD.h"

namespace fmBotConnect
{
       REQEST_UPLOAD::REQEST_UPLOAD(std::string _ID, int _CHUNKCount, std::string _MD5) {
            jANSTMSG = ANSTMSG::REQEST_UPLOAD;
            ID = _ID;
            CHUNK_COUNT = _CHUNKCount;
            MD5 = _MD5;
            IsWaitForAck = true;
        }
        
        std::string REQEST_UPLOAD::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            CATEGORY_TYPES _CATEGORY_TYPES;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::UPLOAD_END) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");  
            
            json = json.append(" \"CHUNK_COUNT\" : \"" + std::to_string(CHUNK_COUNT) + "\" , ");

            json = json.append(" \"MD5\" : \"" + MD5 + "\" , ");

            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void REQEST_UPLOAD::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();
            CHUNK_COUNT = jObj["CHUNK_COUNT"].get<int>();
            MD5 = jObj["MD5"].get<std::string>();
        }
}