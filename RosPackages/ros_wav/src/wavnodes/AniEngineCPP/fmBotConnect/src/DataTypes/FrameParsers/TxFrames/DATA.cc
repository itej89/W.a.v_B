
#include "DataTypes/FrameParsers/TxFrames/DATA.h"

namespace fmBotConnect
{
       DATA::DATA(std::string _ID, CATEGORY_TYPES::CODE _TYPE, std::vector<uint8_t> _DATA, int _BLOCK_COUNT) {
            jANSTMSG = ANSTMSG::DATA;
            ID = _ID;
            CATEGORY_TYPE = _TYPE;
            DATA_BYTES.insert(DATA_BYTES.begin(), _DATA.begin(), _DATA.end());
            BLOCK_COUNT = _BLOCK_COUNT;
            IsWaitForAck = true;
        }
        
        std::string DATA::Json()
        {
            std::string json = "";

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            CATEGORY_TYPES _CATEGORY_TYPES;
            COMMAND_TYPES _COMMAND_TYPES;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::UPLOAD_END) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"CATEGORY\" : \"" + _CATEGORY_TYPES.CODE_TO_STRING.at(CATEGORY_TYPE) + "\" , ");

            json = json.append(" \"DATA\" : \"" + std::string(DATA_BYTES.begin(), DATA_BYTES.end()) + "\" , ");

            json = json.append(" \"BLOCK_COUNT\" : \"" + std::to_string(BLOCK_COUNT) + "\" , ");
     
            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void DATA::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();
            BLOCK_COUNT = jObj["BLOCK_COUNT"].get<int>();

            std::string strCategory = jObj["CATEGORY"].get<std::string>();
            CATEGORY_TYPES _CATEGORY;
            CATEGORY_TYPE = _CATEGORY.STRING_TO_CODE.at(strCategory);

            DATA_BYTES.clear();
            std::string base64String = jObj["DATA"].get<std::string>();;
            std::copy(base64String.begin(), base64String.end(), std::back_inserter(DATA_BYTES)); 
        }
}