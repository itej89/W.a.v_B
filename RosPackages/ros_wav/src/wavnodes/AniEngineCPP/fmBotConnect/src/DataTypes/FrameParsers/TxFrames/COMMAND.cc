
#include "DataTypes/FrameParsers/TxFrames/COMMAND.h"

namespace fmBotConnect
{
       COMMAND::COMMAND(std::string _ID) {
            jANSTMSG = ANSTMSG::COMMAND;
            ID = _ID;
            IsWaitForAck = true;
        }


        COMMAND::COMMAND(std::string _ID, CATEGORY_TYPES::CODE  _CATEGORY, COMMAND_TYPES::CODE _COMMAND)
        {
            CATEGORY_TYPE = _CATEGORY;
            COMMAND_TYPE = _COMMAND;
            jANSTMSG = ANSTMSG::COMMAND;
            ID = _ID;
            IsWaitForAck = true;
        }
        
        std::string COMMAND::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            CATEGORY_TYPES _CATEGORY_TYPES;
            COMMAND_TYPES _COMMAND_TYPES;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::UPLOAD_END) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"CATEGORY\" : \"" + _CATEGORY_TYPES.CODE_TO_STRING.at(CATEGORY_TYPE) + "\" , ");

            json = json.append(" \"COMMAND\" : \"" + _COMMAND_TYPES.CODE_TO_STRING.at(COMMAND_TYPE) + "\" , ");
     
            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void COMMAND::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::string strCategory = jObj["CATEGORY"].get<std::string>();
            CATEGORY_TYPES _CATEGORY;
            CATEGORY_TYPE = _CATEGORY.STRING_TO_CODE.at(strCategory);

            std::string strCommand = jObj["COMMAND"].get<std::string>();
            COMMAND_TYPES _COMMAND;
            COMMAND_TYPE = _COMMAND.STRING_TO_CODE.at(strCommand);
        }
}