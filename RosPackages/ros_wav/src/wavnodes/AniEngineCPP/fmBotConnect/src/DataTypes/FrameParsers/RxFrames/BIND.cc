#include <iostream>
#include "DataTypes/FrameParsers/RxFrames/BIND.h"


namespace fmBotConnect
{
    
        BIND::BIND(){}

        BIND::BIND(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::BIND;
            ID = _ID;
        }

        void BIND::ParseJson(std::string Json)
        {
            RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();


            std::cout<< "Parsing Bind Info" << std::endl;
            jsonObject jObjBIND_INFO =   jObj["BIND_INFO"];
            
            LINK_ANCHORS _LINK_ANCHORS;

            for(auto it = jObjBIND_INFO.begin(); it != jObjBIND_INFO.end(); ++it)
            {
                BIND_INFO.insert({_LINK_ANCHORS.STRING_TO_CODE[it.key()], jObjBIND_INFO[it.key()].get<std::string>()});
            }
            std::cout<< "Parsed Bind Info" << std::endl;
        }
   
}