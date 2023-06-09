
#include "DataTypes/Enums/LINK_ANCHORS.h"

#include "DataTypes/FrameParsers/TxFrames/LINK.h"

namespace fmBotConnect
{
       LINK::LINK(std::string _ID,  std::map<LINK_ANCHORS::CODE, std::string> _INFO) {
            jANSTMSG = ANSTMSG::LINK;
            
            for (auto it = _INFO.begin(); it != _INFO.end(); it++ )
            {
                LINK_INFO.insert({it->first, it->second});
            }
            ID = _ID;
            IsWaitForAck = true;
        }
        
        std::string LINK::Json()
        {
            std::string json;

            json = json.append("{");

            ANSTMSG _ANSTMSG;
            CATEGORY_TYPES _CATEGORY_TYPES;
            COMMAND_TYPES _COMMAND_TYPES;
            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::LINK) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"LINK_INFO\" : { " );

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = LINK_INFO.begin(); it != LINK_INFO.end(); it++ )
            {
                if(it != --LINK_INFO.end())
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " , ");
                else
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " ");
            }

            json = json.append(" } , ");

            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void LINK::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::map<std::string, std::string> strLINK_INFO = jObj["LINK_INFO"].get<std::map<std::string, std::string>>();
            LINK_INFO.clear();

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = strLINK_INFO.begin(); it != strLINK_INFO.end(); it++ )
            {
                LINK_INFO.insert({_LINK_ANCHORS.STRING_TO_CODE.at(it->first), it->second});
            }
        }
}