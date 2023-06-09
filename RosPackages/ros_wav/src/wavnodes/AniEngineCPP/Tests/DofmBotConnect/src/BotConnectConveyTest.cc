#include <unistd.h>
#include "BotConnectConveyTest.h"


    BotConnectConveyTest::BotConnectConveyTest()
    {

    }

    void BotConnectConveyTest::DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots)
    {
        if(Bots.size() > 0)
        BotConnectManager::Instance->BeginConnectToBot(Bots[0]->Name.IPAddress);
    }
        
    void BotConnectConveyTest::BotConnected(std::string _ID){
        BotConnectManager::Instance->SendLinkInfo();
    }

    void BotConnectConveyTest::BotDisconnected(std::string _ID){
        BotConnectManager::Instance->StartBotScanBroadCastMessage();
    }

    void BotConnectConveyTest::BotLowStorage(){

    }

    void BotConnectConveyTest::BotError(BotConnectionInfo::CODE Error){
            usleep(1000000);
            BotConnectManager::Instance->SendStreamData("hellow stream!!");
    }

    void BotConnectConveyTest::BrokerConenctionChanged(bool  Status){

    }