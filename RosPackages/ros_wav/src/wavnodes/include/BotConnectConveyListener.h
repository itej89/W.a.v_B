#pragma once


#include "DataTypes/BotConnectManager.h"
#include "DataTypes/Delegates/BotConnectConvey.h"

#include "GoalManager.h"

using namespace fmBotConnect;

class BotConnectConveyListener: public BotConnectConvey
{
    public:
        BotConnectionInfo::CODE Awaiting_ACK;
        bool IsReady = true;

        static std::shared_ptr<GoalManager> _goalManager;

       enum PULSE_OXY_STATES {BEGIN_STREAM, INPROGRESS_STREAM, END_STREAM, NA};
       PULSE_OXY_STATES PULSE_OXY_STATE = NA;

        BotConnectConveyListener(std::shared_ptr<GoalManager> _GoalManager);  

        void DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots);
        
        void BotConnected(std::string _ID);
        void BotDisconnected(std::string _ID);
        
        void BotLowStorage();
        void BotError(BotConnectionInfo::CODE Error);
        
        void BrokerConenctionChanged(bool  Status);

        void AwaitACK(BotConnectionInfo::CODE _Awaiting_ACK);

        bool IsACKRecieved();

        void BotStartLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS);

        void BotStopLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS);

        void BotRequest(LINK_ANCHORS::CODE, std::string _REQUEST_DATA);

        static void * loop(void *threadid);
};