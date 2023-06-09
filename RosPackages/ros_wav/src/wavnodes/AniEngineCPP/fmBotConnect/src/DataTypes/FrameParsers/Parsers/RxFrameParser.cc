
#include <iostream>
#include "DataTypes/FrameParsers/Parsers/RxFrameParser.h"

namespace fmBotConnect
{
       std::pair<ANIMSG::CODE, std::shared_ptr<RxBaseFrame>> RxFrameParser::GetBaseFrame(std::string Json)
        {
            std::cout<< "Parsing Base Frame" << std::endl;
            std::pair<ANIMSG::CODE, std::shared_ptr<RxBaseFrame>> baseFrame = std::make_pair(ANIMSG::NA, std::make_shared<RxBaseFrame>());
            baseFrame.second->ParseJson(Json);
            baseFrame.first = baseFrame.second->jANIMSG;
            return baseFrame;
        }
        
        std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>>  RxFrameParser::GetRxObject(std::string Json)
        {
            std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>> baseFrame = std::make_pair(ANIMSG::NA, std::make_shared<RxBaseFrame>());
            baseFrame.second->ParseJson(Json);
                switch(baseFrame.second->jANIMSG) {
                case ANIMSG::CATEGORY_ACK:
                    baseFrame =  std::make_pair(ANIMSG::CATEGORY_ACK, std::make_shared<CATEGORY_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::DATA_ACK:
                    baseFrame =  std::make_pair(ANIMSG::DATA_ACK, std::make_shared<DATA_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::COMMAND_ACK:
                    baseFrame =  std::make_pair(ANIMSG::COMMAND_ACK, std::make_shared<COMMAND_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::REQEST_UPLOAD_ACK:
                    baseFrame =  std::make_pair(ANIMSG::REQEST_UPLOAD_ACK, std::make_shared<REQEST_UPLOAD_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::UPLOAD_END_ACK:
                    baseFrame =  std::make_pair(ANIMSG::UPLOAD_END_ACK, std::make_shared<UPLOAD_END_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::LINK_ACK:
                    baseFrame =  std::make_pair(ANIMSG::LINK_ACK, std::make_shared<LINK_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::STREAM_ACK:
                    baseFrame =  std::make_pair(ANIMSG::STREAM_ACK, std::make_shared<STREAM_ACK>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::REQUEST:
                    std::cout<< "Parsing Request Frame" << std::endl;
                    baseFrame =  std::make_pair(ANIMSG::REQUEST, std::make_shared<REQUEST>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::BIND:
                    std::cout<< "Parsing Bind Frame" << std::endl;
                    baseFrame =  std::make_pair(ANIMSG::BIND, std::make_shared<BIND>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::UNBIND:
                    std::cout<< "Parsing UnBind Frame" << std::endl;
                    baseFrame =  std::make_pair(ANIMSG::UNBIND, std::make_shared<UNBIND>());
                    baseFrame.second->ParseJson(Json);
                    break;
                case ANIMSG::NA:
                    break;
            }
                return baseFrame;
            
        }
}