#include "BotConnectConveyListener.h"


    std::shared_ptr<GoalManager> BotConnectConveyListener::_goalManager;

    BotConnectConveyListener::BotConnectConveyListener(std::shared_ptr<GoalManager> _GoalManager)
    {
            BotConnectConveyListener::_goalManager = _GoalManager;
    }

    void BotConnectConveyListener::DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots)
    {
        if(Bots.size() > 0)
        BotConnectManager::Instance->BeginConnectToBot(Bots[0]->Name.IPAddress);
    }
        
    void BotConnectConveyListener::BotConnected(std::string _ID){
        BotConnectManager::Instance->SendLinkInfo();
    }

    void BotConnectConveyListener::BotDisconnected(std::string _ID){
        BotConnectManager::Instance->StartBotScanBroadCastMessage();
    }

    void BotConnectConveyListener::BotLowStorage(){

    }

    void BotConnectConveyListener::BotError(BotConnectionInfo::CODE Error){
        if(Awaiting_ACK == Error)
        {
         std::cout << "ACK recieved!" << std::endl;
        }
        IsReady = true;
        Awaiting_ACK = BotConnectionInfo::CODE::ERROR;
    }

    void BotConnectConveyListener::BrokerConenctionChanged(bool  Status){

    }

    void BotConnectConveyListener::AwaitACK(BotConnectionInfo::CODE _Awaiting_ACK)
    {
        IsReady = false;
        Awaiting_ACK = _Awaiting_ACK;
    }

    bool BotConnectConveyListener::IsACKRecieved()
    {
        return IsReady;
    }

    void BotConnectConveyListener::BotStartLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS)
    {
        if(PULSE_OXY_STATE != INPROGRESS_STREAM)
            PULSE_OXY_STATE = BEGIN_STREAM;
    }

    void BotConnectConveyListener::BotStopLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS)
    {
        if(PULSE_OXY_STATE != NA)
            PULSE_OXY_STATE = END_STREAM;
    }

    void * BotConnectConveyListener::loop(void *threadid) {
        std::cout << "Sending goal! " << std::endl;
            _goalManager->SendGoal(-4.0, -4.0, 0.0, 0.0, 0.0, -0.7141, 0.6991);
            _goalManager->SendGoal(0.7157, 0.7093, 0.0, 0.0, 0.0, -0.0110, 0.9999);
    }

    
    void BotConnectConveyListener::BotRequest(LINK_ANCHORS::CODE, std::string _REQUEST_DATA)
    {
        std::cout << "BotRequest recieved! : "<< _REQUEST_DATA << std::endl;

        if(_REQUEST_DATA == "KITCHEN LOOP")
        {
            std::cout << "BotRequest KITCHENLOOP! : "<< _REQUEST_DATA << std::endl;
            pthread_t SendThread;
            long id =3;
    
            int  rc = pthread_create(&SendThread, NULL, &BotConnectConveyListener::loop, (void *)id);
                
            if (rc) {
                printf("Eror:unable to create thread!");
                exit(-1);
            }

        }
    }