#include <unistd.h>
#include <functional>
#include <memory>

#include "BotConnectManagerTest.h"
#include "BotConnectConveyTest.h"

    BotConnectManagerTest::BotConnectManagerTest(){

    }


    TEST_F(BotConnectManagerTest, BotConnectManagerTest) {
        
         std::shared_ptr<BotConnectConveyTest> _BotConnectConveyTest(new BotConnectConveyTest());
         BotConnectManager::Instance->Initialize(_BotConnectConveyTest.get());
         BotConnectManager::Instance->StartBotScanBroadCastMessage();

        while(true)
        {
            usleep(3000000);
        }
    }