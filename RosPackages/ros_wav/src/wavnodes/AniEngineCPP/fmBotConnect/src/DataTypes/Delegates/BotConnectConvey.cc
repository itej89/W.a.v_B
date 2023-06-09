
#include "DataTypes/Delegates/BotConnectConvey.h"

namespace fmBotConnect
{
    void BotConnectConvey::DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots){}
    
    void BotConnectConvey::BotConnected(std::string _ID){}
    void BotConnectConvey::BotDisconnected(std::string _ID){}
    
    void BotConnectConvey::BotLowStorage(){}
    void BotConnectConvey::BotError(BotConnectionInfo::CODE Error){}
    
    void BotConnectConvey::BrokerConenctionChanged(bool  Status){}

    void BotConnectConvey::BotStartLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS){}
    void BotConnectConvey::BotStopLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS){}

    void BotConnectConvey::BotRequest(LINK_ANCHORS::CODE _LINK_ANCHORS, std::string DATA){}
}