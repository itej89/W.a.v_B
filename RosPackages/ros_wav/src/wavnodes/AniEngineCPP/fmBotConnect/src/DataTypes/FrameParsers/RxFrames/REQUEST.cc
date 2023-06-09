#include <iostream>

#include "DataTypes/Enums/LINK_ANCHORS.h"

#include "DataTypes/FrameParsers/RxFrames/REQUEST.h"



namespace fmBotConnect
{
       REQUEST::REQUEST(){}
       REQUEST::REQUEST(std::string _ID,  std::map<LINK_ANCHORS::CODE, std::string> _DATA){
            jANIMSG = ANIMSG::REQUEST;
            
            for (auto it = _DATA.begin(); it != _DATA.end(); it++ )
            {
                REQUEST_DATA.insert({it->first, it->second});
            }
            ID = _ID;
        }
        
        std::string REQUEST::Json()
        {
            std::string json;

            json = json.append("{");

            ANIMSG _ANIMSG;

            json = json.append(" \"ANSTMSG\" : \"" + _ANIMSG.CODE_TO_STRING.at(ANIMSG::REQUEST) + "\" , ");
            
            json = json.append(" \"ID\" : \"" + ID + "\" , ");

            json = json.append(" \"STREAM_DATA\" : { " );

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = REQUEST_DATA.begin(); it != REQUEST_DATA.end(); it++ )
            {
                if(it != --REQUEST_DATA.end())
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " , ");
                else
                json = json.append(" \""+_LINK_ANCHORS.CODE_TO_STRING.at(it->first)+"\" : " + it->second + " ");
            }

            json = json.append(" } , ");

            json = json.append(" \"FRAME_ID\" : \"" + FRAME_ID + "\" ");

            json = json.append("}");

            return json;
        }

        void REQUEST::ParseJson(std::string Json)
        {
            
            std::cout<< "Parsing Request : " << Json << std::endl;

            RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            std::map<std::string, std::string> strREQUEST_DATA = jObj["REQUEST_DATA"].get<std::map<std::string, std::string>>();
            REQUEST_DATA.clear();

            LINK_ANCHORS _LINK_ANCHORS;
            for (auto it = strREQUEST_DATA.begin(); it != strREQUEST_DATA.end(); it++ )
            {
                REQUEST_DATA.insert({_LINK_ANCHORS.STRING_TO_CODE.at(it->first), it->second});
            }
        }
}