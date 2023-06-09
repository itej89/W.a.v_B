#include <functional>
#include <algorithm>

#include "Framework/TransportLayer/Helpers/TransportLayerHelper.h"
#include "DataTypes/BotConnectManager.h"


namespace fmBotConnect
{
        std::shared_ptr<BotConnectManager> BotConnectManager::Instance(new BotConnectManager());

        bool BotConnectManager::ipComparision(std::shared_ptr<BotDetails> & obj, string ip)
        {
            if(obj->Name.IPAddress == ip)
                return true;
            else
                return false;
        }

        //DOIPContextConvey
         void BotConnectManager::FoundDOIPEntity(DOIPEntity Entity) {
           auto it = std::find_if(Bots.begin(), Bots.end(), std::bind(BotConnectManager::ipComparision,  std::placeholders::_1 , Entity.IPAddress) );
            if(it != Bots.end())
            {
                it->get()->IsResponded = true;
            }
            else
            {
                std::shared_ptr<BotDetails> bot(new BotDetails());
                bot->Name = Entity;
                bot->IsResponded = true;
                Bots.push_back(bot);
                if(botDelegate != nullptr)
                {
                    botDelegate->DiscoveredBots(Bots);
                }
            }
        }
        
        void BotConnectManager::UDSResponseRecieved(std::vector<uint8_t> response) {
            std::string strFrame(response.begin(), response.end());
            
            RxFrameParser rxFrameParser;
            if(strFrame != "")
            {
                std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>> state = rxFrameParser.GetBaseFrame(strFrame);
                if(state.first != ANIMSG::NA)
                {
                    FrameRecieved(state.second->jANIMSG, strFrame);
                }
                
            }
        }
        //End of DOIPContextConvey



        //DOIPContextResultConvey
    void BotConnectManager::InitializeResultNotify(int result) {
        
    }
    
    void BotConnectManager::UDSSendResultNotify(int result) {
        
    }
    
    void BotConnectManager::LinkDisconnected() {
        if(ConnectedBot != nullptr)
        {
           auto it = std::find_if(Bots.begin(), Bots.end(), std::bind(BotConnectManager::ipComparision,  std::placeholders::_1 , ConnectedBot->Name.IPAddress));
           if(it != Bots.end())
           Bots.erase(it);

            if(botDelegate != nullptr)
            {
                botDelegate->DiscoveredBots(Bots);
            }
             ConnectedBot = nullptr;
            botDelegate->BotDisconnected("");
           
        }
    }

    void BotConnectManager::LinkConnected(IPEndPoint EndPoint) {
       
        BotConnectTimeout.stop();
        
        if(botDelegate != nullptr)
        {
            auto it = std::find_if(Bots.begin(), Bots.end(), std::bind(BotConnectManager::ipComparision,  std::placeholders::_1 , EndPoint.IPAddress) );
           if(it != Bots.end())
            {
                it->get()->IsConnected = true;
                ConnectedBot = *it;

                botDelegate->BotConnected(EndPoint.IPAddress);
            }
        }
    }
    //End of DOIPContextResultConvey
    

    void BotConnectManager::FrameRecieved(ANIMSG::CODE FrameType, std::string Json) {
        RxFrameParser rxFrameParser;
        std::pair<ANIMSG::CODE,std::shared_ptr<RxBaseFrame>> state = rxFrameParser.GetRxObject(Json);
        switch(FrameType) {
        case ANIMSG::CATEGORY_ACK:
        {
            std::shared_ptr<RxBaseFrame> rxshrd_ptr = state.second;
            if((std::dynamic_pointer_cast<CATEGORY_ACK>(rxshrd_ptr))->jACK == ACK::OK)
            {
                if(CategoryFrameID == (std::dynamic_pointer_cast<CATEGORY_ACK>(rxshrd_ptr))->FRAME_ID)
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::CATEGORY_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            break;
        }
        case ANIMSG::COMMAND_ACK:
            if((std::dynamic_pointer_cast<COMMAND_ACK>(state.second))->jACK == ACK::OK)
            {
                if(CommandAckFrameID == (std::dynamic_pointer_cast<COMMAND_ACK>(state.second))->FRAME_ID)
                {
                
                    
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::COMMAND_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            break;
        case ANIMSG::DATA_ACK:
    
            if((std::dynamic_pointer_cast<DATA_ACK>(state.second))->jACK == ACK::OK)
            {
                if(DataFrameID == (std::dynamic_pointer_cast<DATA_ACK>(state.second))->FRAME_ID)
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::SENDDATA_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            break;
        case ANIMSG::REQEST_UPLOAD_ACK:
            if((std::dynamic_pointer_cast<REQEST_UPLOAD_ACK>(state.second))->jACK == ACK::OK)
            {
                if(ReqUploadFrameID == (std::dynamic_pointer_cast<REQEST_UPLOAD_ACK>(state.second))->FRAME_ID)
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::REQUP_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            break;
        case ANIMSG::UPLOAD_END_ACK:
            if((std::dynamic_pointer_cast<UPLOAD_END_ACK>(state.second))->jACK == ACK::OK)
            {
                if(ExUploadFrameID == (std::dynamic_pointer_cast<UPLOAD_END_ACK>(state.second))->FRAME_ID )
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::EXREQ_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            break;
        case ANIMSG::LINK_ACK:
    
            if((std::dynamic_pointer_cast<LINK_ACK>(state.second))->jACK == ACK::OK)
            {
                if(LinkFrameID == (std::dynamic_pointer_cast<LINK_ACK>(state.second))->FRAME_ID)
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::LINK_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            
            break;
        case ANIMSG::STREAM_ACK:
    
            if((std::dynamic_pointer_cast<STREAM_ACK>(state.second))->jACK == ACK::OK)
            {
                if(StreamFrameID == (std::dynamic_pointer_cast<STREAM_ACK>(state.second))->FRAME_ID)
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::STREAM_ACK);
                    }
                }
                else
                {
                    if(botDelegate != nullptr)
                    {
                        botDelegate->BotError(BotConnectionInfo::ERROR);
                    }
                }
            }
            else
            {
                if(botDelegate != nullptr)
                {
                    botDelegate->BotError(BotConnectionInfo::ERROR);
                }
            }
            
            break;
        case ANIMSG::REQUEST:
            std::cout<< "Request recieved" << std::endl;
            if(botDelegate != nullptr)
            {
                 LINK_ANCHORS _LINK_ANCHORS;
                for(auto it = std::dynamic_pointer_cast<REQUEST>(state.second)->REQUEST_DATA.begin(); it != std::dynamic_pointer_cast<REQUEST>(state.second)->REQUEST_DATA.end(); ++it)
                {
                    botDelegate->BotRequest(it->first, it->second);
                }

                SendRequestAck();
            }
            break;
            
        case ANIMSG::BIND:
            std::cout<< "Bind recieved" << std::endl;
            if(botDelegate != nullptr)
            {
                 LINK_ANCHORS _LINK_ANCHORS;
                for(auto it = std::dynamic_pointer_cast<BIND>(state.second)->BIND_INFO.begin(); it != std::dynamic_pointer_cast<BIND>(state.second)->BIND_INFO.end(); ++it)
                {
                    botDelegate->BotStartLinkStream(it->first);
                }
                
            }
            break;

            case ANIMSG::UNBIND:
            std::cout<< "UnBind recieved" << std::endl;
            if(botDelegate != nullptr)
            {
                 LINK_ANCHORS _LINK_ANCHORS;
                for(auto it = std::dynamic_pointer_cast<UNBIND>(state.second)->UNBIND_INFO.begin(); it != std::dynamic_pointer_cast<UNBIND>(state.second)->UNBIND_INFO.end(); ++it)
                {
                    botDelegate->BotStopLinkStream(it->first);
                }
                
            }
            
            break;
        default:
            break;
            
        }
    }
    

    void BotConnectManager::Initialize(BotConnectConvey* delegate)
    {
        botDelegate = delegate;
        IsInitialized = DOIPAccessImplementation::Instance->Initialize(this, this);
    }
    
    
    void BotConnectManager::UnInitialize()
    {
        IsInitialized = false;
        DOIPAccessImplementation::Instance->Uninitialize();
    }


    void BotConnectManager::SendScanFrame() {
      
        // int i = 0;
        // while(i < Bots.count)
        // {
        //     if(!Bots[i].IsResponded)
        //     {
        //         Bots.remove(at: i)
        //         i = i - 1
        //     }
        //     i = i + 1
        // }
        
        // if(botDelegate != nil)
        // {
        //     botDelegate.DiscoveredBots(Bots: Bots)
        // }
        
        // for bot in Bots
        // {
        //     if(!bot.IsConnected)
        //     {
        //         bot.IsResponded = false
        //     }
        // }
            
         DOIPAccessImplementation::Instance->SendScan();
        
    }
    
    void BotConnectManager::StartBotScanBroadCastMessage()
    {
        ScanRetryTimer.stop();
//        for bot in Bots
//        {
//            if(!bot.IsConnected)
//            {
//                bot.IsResponded = false
//            }
//        }
       ResumeScan();
    }
    
    void BotConnectManager::ResumeScan()
    {
        Bots.clear();
        
        if(ConnectedBot != nullptr)
        {
            Bots.push_back(ConnectedBot);
            if(botDelegate != nullptr)
           {
               botDelegate->DiscoveredBots(Bots);
           }
        }
        
        SendScanFrame();
       
        std::function<void(void)>  ScanRetryLooper = std::bind(&BotConnectManager::SendScanFrame ,this);
        ScanRetryTimer.setIntervalTimer(ScanRetryLooper, 4000);
    }
    
    void BotConnectManager::StopBotScanBroadCastMessage()
    {
        ScanRetryTimer.stop();
    }
    
    void BotConnectManager::BotConnectFailed()
    {
       StartBotScanBroadCastMessage();
    }
    
    void BotConnectManager::BeginConnectToBot(std::string _ID)
    {
        StopBotScanBroadCastMessage();

         auto it = std::find_if(Bots.begin(), Bots.end(), std::bind(BotConnectManager::ipComparision,  std::placeholders::_1 , _ID) );
           if(it != Bots.end())
           {
                DOIPAccessImplementation::Instance->Connect(it->get()->Name);
           }
        
        std::function<void(void)>  BotConnectLooper = std::bind(&BotConnectManager::BotConnectFailed ,this);
        BotConnectTimeout.setTimeoutTimer(BotConnectLooper, 30000);
    }
    
    void BotConnectManager::BeginDisconnectBot()
    {
        if(ConnectedBot != nullptr)
        {
            DOIPAccessImplementation::Instance->Disconnect();
            
            auto it = std::find_if(Bots.begin(), Bots.end(), std::bind(BotConnectManager::ipComparision,  std::placeholders::_1 , ConnectedBot->Name.IPAddress) );
            if(it != Bots.end())
            {
                it->get()->IsConnected = false;
            }
            
            if(botDelegate != nullptr)
            {
                botDelegate->DiscoveredBots(Bots);
            }

            ConnectedBot = nullptr;
        }
    }

      //MqttAccess 
    void BotConnectManager::SendRequestAck()
    {
            std::cout<< "Sending Request ACK" << std::endl;
        if(ConnectedBot != nullptr)
        {
            TransportLayerHelper _TransportLayerHelper;
            std::string strIP = _TransportLayerHelper.getWiFiAddress();
            REQUEST_ACK TxFrame(ID, ACK::OK);
            std::string txJson = TxFrame.Json();
            std::cout<< "Request ACK :  "<< txJson << std::endl;
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
        }
    }

    void BotConnectManager::SendStreamData(std::string Data)
    {
        if(ConnectedBot != nullptr)
        {
            TransportLayerHelper _TransportLayerHelper;
            std::string strIP = _TransportLayerHelper.getWiFiAddress();
            std::map<LINK_ANCHORS::CODE, std::string> _STREAM_DATA = {
                {LINK_ANCHORS::HEART_MONITOR, Data}
            };
            STREAM TxFrame(ID, _STREAM_DATA);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            StreamFrameID = TxFrame.FRAME_ID;
        }
    }

    void BotConnectManager::SendLinkInfo()
    {
        if(ConnectedBot != nullptr)
        {
            TransportLayerHelper _TransportLayerHelper;
            std::string strIP = _TransportLayerHelper.getWiFiAddress();
            std::map<LINK_ANCHORS::CODE, std::string> _LINK_INFO = {
                // {LINK_ANCHORS::JOY, "{ \"BIND_TYPE\":\"BTHID\", \"DATA\":\"20:14:08:13:25:70\"}"},
                // {LINK_ANCHORS::HEART_MONITOR, "{ \"BIND_TYPE\":\"SERVER\", \"DATA\":\"http://"+strIP+":18080\"}"}
                {LINK_ANCHORS::NAVIGATION, "{ \"BIND_TYPE\":\"NA\", \"DATA\":\"\"}"}                
            };
            LINK TxFrame(ID, _LINK_INFO);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            LinkFrameID = TxFrame.FRAME_ID;
        }
    }

    void BotConnectManager::SetANIActionMode(CATEGORY_TYPES::CODE _CATEGORY) 
    {
        if(ConnectedBot != nullptr)
        {
            CATEGORY TxFrame(ID, _CATEGORY);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            CategoryFrameID = TxFrame.FRAME_ID;
        }
    }
    
    void BotConnectManager::RequestUpload(int _Count, std::string _MD5)
    {
        if(ConnectedBot != nullptr)
        {
            REQEST_UPLOAD TxFrame(ID, _Count, _MD5);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            ReqUploadFrameID =  TxFrame.FRAME_ID;
        }
    }
    
    void BotConnectManager::SendData(CATEGORY_TYPES::CODE  _CATEGORY, std::vector<uint8_t> _Data, int _Block_Count)  
    {
        if(ConnectedBot != nullptr)
        {
            DATA TxFrame(ID, _CATEGORY,_Data, _Block_Count);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            DataFrameID = TxFrame.FRAME_ID;
        }
    }
    
    void BotConnectManager::ExitUpload()
    {
        if(ConnectedBot != nullptr)
        {
            UPLOAD_END TxFrame(ID);
            std::string txJson = TxFrame.Json();
            DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
            ExUploadFrameID = TxFrame.FRAME_ID;
        }
    }
    
    void BotConnectManager::SendCommand(CATEGORY_TYPES::CODE  _CATEGORY, COMMAND_TYPES::CODE _COMMAND) {
        COMMAND TxFrame(ID,  _CATEGORY, _COMMAND);
        std::string txJson = TxFrame.Json();
        DOIPAccessImplementation::Instance->SendData(std::vector<uint8_t>(txJson.begin(), txJson.end()));
        CommandAckFrameID = TxFrame.FRAME_ID;
    }
    //End of MqttAccess

}