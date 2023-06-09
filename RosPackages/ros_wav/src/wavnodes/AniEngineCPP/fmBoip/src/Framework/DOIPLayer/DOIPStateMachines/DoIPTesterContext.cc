
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/TransportLayer/UDPListen.h"
#include "Framework/DataTypes/Extras/TransportClientConvey.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DoIPTesterContext.h"

#include "Framework/DOIPFrameHelpers/DOIPFrameParser.h"



namespace fmBoip
{
    IDiagState* DoIPTesterContext::getCurrentState()
    {
        return _currentState;
    }
    
    void DoIPTesterContext::setCurrentState(IDiagState* newState)
    {
        _currentState = newState;
    }
    
    IDiagState* DoIPTesterContext::getPreviousState()
    {
        return _previousState;
    }

    void DoIPTesterContext::setPreviousState(IDiagState* oldState)
    {
        _previousState = oldState;
    }
    
    DoIPTesterContext::DoIPTesterContext()
    {
       
    }
    
  
    void DoIPTesterContext::ParseTCPData(RecievedData recData)
    {
        int i = 0;
        while(i < TCPDataBuffer.size())
        {
            if(TCPDataBuffer[i].RemoteEndPoint.IPAddress == recData.RemoteEndPoint.IPAddress && TCPDataBuffer[i].RemoteEndPoint.Port == recData.RemoteEndPoint.Port)
            {

                while(TCPDataBuffer[i].recvBuffer.size() >= DOIPResponseObject::GetHeaderLength())
                {
                    DOIPFrameParser parser;
                    DOIPResponseObject objRespone;
                    if(parser.Parse(TCPDataBuffer[i].recvBuffer, objRespone))
                    {
                        objRespone.EndPoint = TCPDataBuffer[i].RemoteEndPoint;
                        if(DOIPResponseObject::GetHeaderLength() + objRespone.GetPayloadLength() == TCPDataBuffer[i].recvBuffer.size())
                        {
                            DOIPBuffer.push_back(std::make_pair(true, objRespone));
                            std::cout << objRespone.GetPayLoadType() << std::endl;
                            TCPDataBuffer.erase(TCPDataBuffer.begin()+i);
                            i = i - 1;
                            break;
                        }
                        else
                        {
                            if(DOIPResponseObject::GetHeaderLength() + objRespone.GetPayloadLength() < TCPDataBuffer[i].recvBuffer.size())
                            {
                                int FirstFrameLength = DOIPResponseObject::GetHeaderLength() + objRespone.GetPayloadLength();

                                DOIPBuffer.push_back(std::make_pair(true, objRespone));
                                TCPDataBuffer[i].recvBuffer.erase(TCPDataBuffer[i].recvBuffer.begin(), TCPDataBuffer[i].recvBuffer.begin()+FirstFrameLength);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
                break;
            }
            
            i = i + 1;
        }
    }

    
    
    //DOIP Communication Initializing sequence
    int DoIPTesterContext::_Initialize(DOIPContextConvey* _ContextConvey, DOIPContextResultConvey* _ResultConvey)
    {
        TcpClient::Instance->ClientConvey.reset(this);
        UDPListen::Instance->UDPClientConvey.reset(this);

         ResultConvey = _ResultConvey;
         ContextConvey = _ContextConvey;
         UDPListen::Instance->StartListening();
        StartDataParserLoop();
        return DIAGNOSTIC_STATUS::SUCCESS;
    }
    
    void DoIPTesterContext::_UnInitialize()
    {
        UDPListen::Instance->StopListening();
        TcpClient::Instance->Disconnect();
    }

    int DoIPTesterContext::MoveNext(std::vector<uint8_t> dataToBeSent) 
    {
        return dynamic_cast<IDiagStateForSendRecieve*>(_currentState)->_Init(dataToBeSent);
    }

    
    int DoIPTesterContext::AnnounceDiscover() 
    {
        Vehicle_Identification_Types::CODE typeCode = Vehicle_Identification_Types::Instance->DECODE(DOIPParameters::Instance->DOIP_IDENTIFICATION_MODE);
        
        std::map<Vehicle_Identification_Types::CODE, std::shared_ptr<IDiagState>>::iterator it = identificationType_DiagState.find(typeCode);
        
        if(it != identificationType_DiagState.end())
        {
            setCurrentState(identificationType_DiagState.at(typeCode).get());
        }
        
        if(typeCode == Vehicle_Identification_Types::VEHICLE_IDENTIFICATION || typeCode == Vehicle_Identification_Types::VEHICLE_IDENTIFICATION_EID || typeCode == Vehicle_Identification_Types::VEHICLE_IDENTIFICATION_VIN)
        {
            DOIPSession::Instance->RemoteEndPoint = IPEndPoint( DOIPParameters::Instance->DOIP_Entity_IPAddress,  DOIPParameters::Instance->DOIP_ENTITY_UDP_DISCOVER);
        }
        
        return MoveNext(std::vector<uint8_t>());
    }
    
    int DoIPTesterContext::RoutingActivation(DOIPEntity Entity)
    {
        DOIPSession::Instance->TargetAddress = Entity.LogicalAddress;
        DOIPSession::Instance->FurtherAction = Entity.FurtherActions;
        DOIPSession::Instance->UDSRequestType = ADDRESSING_TYPES::UDSRequestType::UDS;
      
        dynamic_cast<RoutingActivationDiagState*>(payloadType_DiagState.at(Response_Payload_Types::PLD_ROUTING_ACTIVATION_RES).get())->RemoteEndPoint = IPEndPoint(Entity.IPAddress, DOIPParameters::Instance->DOIP_ENTITY_UDP_DISCOVER);
      
        DOIPSession::Instance->RemoteEndPoint = IPEndPoint(Entity.IPAddress, DOIPParameters::Instance->DOIP_ENTITY_UDP_DISCOVER);
        setCurrentState(payloadType_DiagState.at(Response_Payload_Types::PLD_ROUTING_ACTIVATION_RES).get());
        return MoveNext(std::vector<uint8_t>());
    }
    
    void DoIPTesterContext::HandleIncomingData(DOIPResponseObject data)
    {
        Response_Payload_Types::CODE  responseCode = data.GetPayLoadType();
        
        if(payloadType_DiagState.find(data.GetPayLoadType()) != payloadType_DiagState.end())
        {
            setCurrentState(payloadType_DiagState.at(responseCode).get());
        }
        
          std::cout << "\nIP : " << DOIPSession::Instance->RespondedDOIPEntityCachedData.IPAddress << "\n Port : " << DOIPSession::Instance->RespondedDOIPEntityCachedData.Port << std::endl;

        
        std::pair<int, std::vector<uint8_t>> returnStatus = _currentState->HandleIncomingData(data);
        
        if(returnStatus.first != (DIAGNOSTIC_STATUS::SUCCESS))
        {
            if(ResultConvey != nullptr)
            {
                ResultConvey->InitializeResultNotify(returnStatus.first);
            }
        }
    }
    
    void DoIPTesterContext::HandleDiagnostic(DOIPResponseObject objResponse)
    {
            setCurrentState(payloadType_DiagState.at(Response_Payload_Types::PLD_DIAG_MESSAGE).get());
            
            std::pair<int, std::vector<uint8_t>> returnStatus = _currentState->HandleIncomingData(objResponse);
            
            if(ContextConvey != nullptr)
            {
                ResultConvey->UDSSendResultNotify(returnStatus.first);
            }
    }
    
    void DoIPTesterContext::HandleDiagAcknowledgement(DOIPResponseObject data)
    {
        if(_currentState != nullptr)
        {
            if(_currentState->GetStateID() != payloadType_DiagState.at(data.GetPayLoadType())->GetStateID())
            {
                if(payloadType_DiagState.find(data.GetPayLoadType()) != payloadType_DiagState.end())
                {
                    setCurrentState(payloadType_DiagState.at(data.GetPayLoadType()).get());
                }
                
                std::pair<int, std::vector<uint8_t>> returnStatus = _currentState->HandleIncomingData(data);
                
                if(ResultConvey != nullptr)
                {
                    if(returnStatus.first != DIAGNOSTIC_STATUS::SUCCESS)
                    {
                        if(TcpClient::Instance->IsTCPConnected())
                        {
                            ResultConvey->UDSSendResultNotify(returnStatus.first);
                        }
                    }
                    else
                    {
                        ResultConvey->UDSSendResultNotify(returnStatus.first);
                    }
                }
            }
        }
    }
    
   

    void DoIPTesterContext::ReadDOIPFrame()
    {
        int i = 0;
        while(i < DOIPBuffer.size()) {
            if(DOIPBuffer[i].second.GetPayLoadType() == Response_Payload_Types::DOIPTester_UNKNOWN_CODE)
            {
                DOIPBuffer.erase(DOIPBuffer.begin()+i);
                i = i - 1;
            }
            else if(DOIPBuffer[i].first)
            {
                if(DoIPGenericHeaderHandler::Instance->ValidateHeader(DOIPBuffer[i].second))
                {
                    if(DOIPBuffer[i].second.GetPayLoadType() == Response_Payload_Types::PLD_DIAG_MESSAGE_POSITIVE_ACK || DOIPBuffer[i].second.GetPayLoadType() == Response_Payload_Types::PLD_DIAG_MESSAGE_NEGATIVE_ACK)
                    {
                        HandleDiagAcknowledgement(DOIPBuffer[i].second);
                    }
                    else if(DOIPBuffer[i].second.GetPayLoadType() == Response_Payload_Types::PLD_DIAG_MESSAGE)
                    {
                        HandleDiagnostic(DOIPBuffer[i].second);
                    }
                    else
                    {
                        HandleIncomingData(DOIPBuffer[i].second);
                    }
                    DOIPBuffer.erase(DOIPBuffer.begin()+i);
                    i = i - 1;
                }
            }
            i = i + 1;
        }
    }

    void DoIPTesterContext::StartDataParserLoop()
    {
        std::function<void(void)>  looper = std::bind(&DoIPTesterContext::ReadDOIPFrame ,this);
        DOIPFrameListener.Start(looper, 1);
    }
    
    void DoIPTesterContext::SendDOIPFrameOverTCP()
    {
        if(TcpClient::Instance->IsTCPConnected() == false)
        {
            if(DOIPFrameSender != nullptr)
            DOIPFrameSender->Stop();
            ResultConvey->LinkDisconnected();
        }
        else
        {
            if(DOIPFrameBuffer.first == true && TcpClient::Instance->IsTCPConnected())
            {
                DOIPFrameBuffer.first = false;
                int result = SendUDSRequest(DOIPFrameBuffer.second);
                ResultConvey->UDSSendResultNotify(result);
            }
        }
    }

    void DoIPTesterContext::StartDOIPSendLoop()
    {
         if(DOIPFrameSender != nullptr)
            DOIPFrameSender->Wait();
         DOIPFrameSender.reset(new fmCommon::ThreadX());
         std::function<void(void)>  looper = std::bind(&DoIPTesterContext::SendDOIPFrameOverTCP ,this);
         DOIPFrameSender->Start(looper, 1);
    }
    
    
    int DoIPTesterContext::SendData(std::vector<uint8_t> Data)
    {
        DOIPFrameBuffer = std::pair<bool, std::vector<uint8_t>>(true, Data);
        TCPDataBuffer.clear();
        return DIAGNOSTIC_STATUS::SUCCESS;
    }
    
    int DoIPTesterContext::SendUDSRequest(std::vector<uint8_t> dataToBeSent)
    {
        int ReturnStatus = -1;
        int retryCount = 0;
        int MaxTransmitRetry = DOIPParameters::Instance->DOIP_DIAG_NO_ACK_REPEAT_NUM;
       do
        {
            setCurrentState(payloadType_DiagState.at(Response_Payload_Types::PLD_DIAG_MESSAGE).get());
            ReturnStatus = MoveNext(dataToBeSent);
            retryCount = retryCount + 1;
        }
       while ((ReturnStatus == DIAGNOSTIC_STATUS::DIAG_ACK_TIMEOUT) && (retryCount <= MaxTransmitRetry));
        
        return ReturnStatus;
    }

     
    
    
    void DoIPTesterContext::FinalizeDiag()
    {
        DOIPFrameListener.Stop();
        if(DOIPFrameSender != nullptr)
        DOIPFrameSender->Stop();
        TcpClient::Instance->Disconnect();
    }
    

    //TransportClientConvey
    void DoIPTesterContext::Disconnected() {
        FinalizeDiag();
        if(ResultConvey != nullptr)
        {
            ResultConvey->LinkDisconnected();
        }
    }
    
    void DoIPTesterContext::DataRecieved(RecievedData recievedData)
    {
        if(recievedData.recvBuffer.size() > 0)
        {
            DOIPSession::Instance->RespondedDOIPEntityCachedData.IPAddress = recievedData.RemoteEndPoint.IPAddress;
            DOIPSession::Instance->RespondedDOIPEntityCachedData.Port = recievedData.RemoteEndPoint.Port;
        
            bool IsFilled = false;
            
            for(int i=0; i < TCPDataBuffer.size(); i++)
            {
                RecievedData recData = TCPDataBuffer[i];
                if(recData.RemoteEndPoint.IPAddress == recievedData.RemoteEndPoint.IPAddress &&
                recData.RemoteEndPoint.Port == recievedData.RemoteEndPoint.Port)
                {
                    recData.recvBuffer.insert(recData.recvBuffer.end(), recievedData.recvBuffer.begin(), recievedData.recvBuffer.end());
                    ParseTCPData(recData);
                    IsFilled = true;
                    break;
                }
            }
            
            if(!IsFilled)
            {
                TCPDataBuffer.push_back(recievedData);
                ParseTCPData(recievedData);
            }
        }
        else
        {
            if(ResultConvey != nullptr)
            ResultConvey->UDSSendResultNotify(DIAGNOSTIC_STATUS::INVALID_HEADER);
        }
    }
    
    void DoIPTesterContext::Timeout(int code) {

        if(ResultConvey != nullptr)
        {
        if(code  == DIAGNOSTIC_STATUS::DIAG_ACK_TIMEOUT)
        {
             ResultConvey->UDSSendResultNotify(code);
        }
        else
        {
            ResultConvey->InitializeResultNotify(code);
        }
        }
    }

    DoIPTesterContext::~DoIPTesterContext()
    {
        
    }
}