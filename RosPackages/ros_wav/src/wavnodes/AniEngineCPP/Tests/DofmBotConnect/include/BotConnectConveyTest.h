#pragma once


#include "DataTypes/BotConnectManager.h"
#include "DataTypes/Delegates/BotConnectConvey.h"


using namespace fmBotConnect;

class BotConnectConveyTest: public BotConnectConvey
{
    public:
        BotConnectConveyTest();  

        void DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots);
        
        void BotConnected(std::string _ID);
        void BotDisconnected(std::string _ID);
        
        void BotLowStorage();
        void BotError(BotConnectionInfo::CODE Error);
        
        void BrokerConenctionChanged(bool  Status);
};