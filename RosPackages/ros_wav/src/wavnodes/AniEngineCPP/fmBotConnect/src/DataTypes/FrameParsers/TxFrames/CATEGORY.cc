
#include "DataTypes/FrameParsers/TxFrames/CATEGORY.h"

namespace fmBotConnect
{
       CATEGORY::CATEGORY(std::string _ID) {
            jANSTMSG = ANSTMSG::CATEGORY;
            ID = _ID;
            IsWaitForAck = true;
        }


        CATEGORY::CATEGORY(std::string _ID, CATEGORY_TYPES::CODE _CODE)
        {
            jANSTMSG = ANSTMSG::CATEGORY;
            ID = _ID;
            TYPE = _CODE;
            IsWaitForAck = true;
        }
        
        std::string CATEGORY::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            CATEGORY_TYPES _CATEGORY_TYPES;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::UPLOAD_END) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"CATEGORY\" : \"" + _CATEGORY_TYPES.CODE_TO_STRING.at(TYPE) + "\" , ");
     
            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void CATEGORY::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strCategory = jObj["CATEGORY"].get<std::string>();
            CATEGORY_TYPES _CATEGORY;
            TYPE = _CATEGORY.STRING_TO_CODE.at(strCategory);
        }
}