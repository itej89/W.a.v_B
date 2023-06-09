#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "Timer.h"

#include "DataTypes/Enums/BotConnectionInfo.h"
#include "DataTypes/Enums/CATEGORY_TYPES.h"
#include "DataTypes/Enums/COMMAND_TYPES.h"

#include "Framework/DataTypes/Extras/DOIPContextConvey.h"
#include "Framework/DataTypes/Extras/DOIPContextResultConvey.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"

#include "DataTypes/BotDetails.h"
#include "DataTypes/Enums/ANIMSG.h"
#include "DataTypes/Enums/LINK_ANCHORS.h"
#include "DataTypes/Delegates/BotConnectConvey.h"
#include "DataTypes/FrameParsers/Parsers/RxFrameParser.h"

#include "DataTypes/FrameParsers/RxFrames/RxBaseFrame.h"
#include "DataTypes/FrameParsers/RxFrames/CATEGORY_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/COMMAND_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/DATA_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/REQEST_UPLOAD_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/UPLOAD_END_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/LINK_ACK.h"
#include "DataTypes/FrameParsers/RxFrames/REQUEST.h"

#include "DataTypes/FrameParsers/TxFrames/TxBaseFrame.h"
#include "DataTypes/FrameParsers/TxFrames/CATEGORY.h"
#include "DataTypes/FrameParsers/TxFrames/COMMAND.h"
#include "DataTypes/FrameParsers/TxFrames/DATA.h"
#include "DataTypes/FrameParsers/TxFrames/REQEST_UPLOAD.h"
#include "DataTypes/FrameParsers/TxFrames/UPLOAD_END.h"
#include "DataTypes/FrameParsers/TxFrames/LINK.h"
#include "DataTypes/FrameParsers/TxFrames/STREAM.h"
#include "DataTypes/FrameParsers/TxFrames/REQUEST_ACK.h"

#include "Framework/DOIPAccessImplementation.h"

#include "UUID.h"
#include "Timer.h"

using namespace fmBoip;

namespace fmBotConnect
{
    class BotConnectManager : public DOIPContextConvey,  DOIPContextResultConvey
    {
        public:
        static std::shared_ptr<BotConnectManager> Instance;

        std::vector<std::shared_ptr<BotDetails>> Bots;
        fmCommon::Timer ScanRetryTimer;
        
        std::shared_ptr<BotDetails> ConnectedBot;
        fmCommon::Timer BotConnectTimeout;
    
        std::string CategoryFrameID = "";
        std::string  CommandAckFrameID = "";
        std::string  DataFrameID = "";
        std::string  ReqUploadFrameID = "";
        std::string  ExUploadFrameID = "";
        std::string  LinkFrameID = "";
        std::string  StreamFrameID = "";
    
        bool IsInitialized = false;

           
        std::string ID =  fmCommon::UUID().stringValue;
        std::string NAME =  "Ani_Studio"+fmCommon::UUID().stringValue;
    


        //DOIPContextConvey
        BotConnectConvey* botDelegate;

       static bool ipComparision(std::shared_ptr<BotDetails> & obj, string ip);

        //DOIPContextConvey
        void FoundDOIPEntity(DOIPEntity Entity);
        
        void UDSResponseRecieved(std::vector<uint8_t> response);
        //End of DOIPContextConvey



        //DOIPContextResultConvey
    void InitializeResultNotify(int result);
    
    void UDSSendResultNotify(int result);
    
    void LinkDisconnected();

    void LinkConnected(IPEndPoint EndPoint);
    //End of DOIPContextResultConvey
    

    void FrameRecieved(ANIMSG::CODE FrameType, std::string Json);

    void Initialize(BotConnectConvey* delegate);
    
    void UnInitialize();


    void SendScanFrame();
    
    void StartBotScanBroadCastMessage();
    
    void ResumeScan();
    
    void StopBotScanBroadCastMessage();
    
    void BotConnectFailed();
    
    void BeginConnectToBot(std::string _ID);
    
    void BeginDisconnectBot();

      //MqttAccess
    void SendRequestAck();

    void SendStreamData(std::string Data);

    void SendLinkInfo();

    void SetANIActionMode(CATEGORY_TYPES::CODE _CATEGORY);
    
    void RequestUpload(int _Count, std::string _MD5);
    
    void SendData(CATEGORY_TYPES::CODE  _CATEGORY, std::vector<uint8_t> _Data, int _Block_Count);
    
    void ExitUpload();
    
    void SendCommand(CATEGORY_TYPES::CODE  _CATEGORY, COMMAND_TYPES::CODE _COMMAND);
    //End of MqttAccess


    };
}
