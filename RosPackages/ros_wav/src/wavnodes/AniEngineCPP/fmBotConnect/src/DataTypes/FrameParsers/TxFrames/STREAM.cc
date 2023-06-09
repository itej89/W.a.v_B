
#include "DataTypes/Enums/LINK_ANCHORS.h"

#include "DataTypes/FrameParsers/TxFrames/STREAM.h"

namespace fmBotConnect
{
       STREAM::STREAM(std::string _ID,  std::map<LINK_ANCHORS::CODE, std::string> _DATA){
            jANSTMSG = ANSTMSG::STREAM;
            
            for (auto it = _DATA.begin(); it != _DATA.end(); it++ )
            {
                STREAM_DATA.insert({it->first, it->second});
            }
            ID = _ID;
            IsWaitForAck = true;
        }
        
        std::string STREAM::Json()
        {
            std::string json;

            json = json.append("{");

            ANSTMSG _ANSTMSG;

            json = json.append(" \"ANSTMSG\" : \"" + _ANSTMSG.CODE_TO_STRING.at(ANSTMSG::STREAM) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"STREAM_DATA\" : { " );

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = STREAM_DATA.begin(); it != STREAM_DATA.end(); it++ )
            {
                if(it != --STREAM_DATA.end())
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " , ");
                else
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " ");
            }

            json = json.append(" } , ");

            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void STREAM::ParseJson(std::string Json)
        {
            TxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::map<std::string, std::string> strSTREAM_DATA = jObj["STREAM_DATA"].get<std::map<std::string, std::string>>();
            STREAM_DATA.clear();

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = strSTREAM_DATA.begin(); it != strSTREAM_DATA.end(); it++ )
            {
                STREAM_DATA.insert({_LINK_ANCHORS.STRING_TO_CODE.at(it->first), it->second});
            }
        }
}