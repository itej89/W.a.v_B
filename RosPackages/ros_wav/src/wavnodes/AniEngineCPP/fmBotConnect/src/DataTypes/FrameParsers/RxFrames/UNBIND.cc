#include "DataTypes/FrameParsers/RxFrames/UNBIND.h"


namespace fmBotConnect
{
        UNBIND::UNBIND(){}

        UNBIND::UNBIND(std::string _ID, ACK::CODE _ACK) {
            jANIMSG = ANIMSG::BIND;
            ID = _ID;
        }

        void UNBIND::ParseJson(std::string Json){
            RxBaseFrame::ParseJson(Json);

            jsonObject jObj =   jsonObject::parse(Json);
            ID = jObj["ID"].get<std::string>();

            jsonObject jObjBIND_INFO =   jObj["UNBIND_INFO"];
            
            LINK_ANCHORS _LINK_ANCHORS;

            for(auto it = jObjBIND_INFO.begin(); it != jObjBIND_INFO.end(); ++it)
            {
                UNBIND_INFO.insert({_LINK_ANCHORS.STRING_TO_CODE[it.key()], jObjBIND_INFO[it.key()].get<std::string>()});
            }
        }
}