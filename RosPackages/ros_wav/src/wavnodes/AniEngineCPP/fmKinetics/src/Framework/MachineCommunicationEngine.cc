 // #include <android/log.h>



#include "Framework/MachineCommunicationEngine.h"

//#include <iostream>


 // #define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "FM_KINETICS", __VA_ARGS__);

namespace fmKinetics
{


     MachineCommunicationEngine::MachineCommunicationEngine()
     {}
     MachineCommunicationEngine::~MachineCommunicationEngine()
     {
         int i=0;
     }


    void MachineCommunicationEngine::KineticsResponseTimeout()
    {

        printf("Kinetics Timeout");
       
        CurrentCommandLoopState = CommandLoopStates::NA;

        UUID Final_Ack = _currentCommsRequestContext.Acknowlegment_Key;
        vector<std::unique_ptr<KineticsResponse>> Final_Response;
        for(int i=0; i<_currentCommsRequestContext.ResponseData.size(); i++)
        {
            Final_Response.push_back(std::move(_currentCommsRequestContext.ResponseData.at(i)));
        }

         printf("Timeout buf count:%d", CommandBuffer.size());

        if(CommandBuffer.size() > 0)
        {
            vector<KineticsRequest> NextData = CommandBuffer.at(0).Command;
            UUID NextAcknowledgementKey = CommandBuffer.at(0).AcknowledgementKey;
            CommandBuffer.erase(CommandBuffer.begin());
           
            StartNextCommandTransmission(NextData,NextAcknowledgementKey);
        }
        else
        {
            _currentCommsRequestContext.IsCurrentCommandProcessingCompleted  = true;
        }
        

        notify_Machine_Comms->KineticsResponseDataTimeout(Final_Ack, std::move(Final_Response));
    }

    void MachineCommunicationEngine::SetCommsDelegate(std::shared_ptr<MachineCommsConvey> delegate)
    {
        notify_Machine_Comms = delegate;
        
         std::shared_ptr<fmSerial::CommsConvey> m_CommsConvey{getPtr()};
        HD_Comms.SetCommsDelegate(m_CommsConvey);
    }

    void MachineCommunicationEngine::InitializeComms()
    {
        HD_Comms.InitializeComms();
    }

    bool MachineCommunicationEngine::IsConnectedToMachine()
    {
        return HD_Comms.IsConnectedToPeripheral();
    }

    void MachineCommunicationEngine::DisconnectMachine()
    {
        HD_Comms.DisconnectDevice();
    }

    void MachineCommunicationEngine::serialStataChanged(CommsStates State) {
    switch (State)
    {
        case CommsStates::READY_TO_SCAN:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::READY_TO_SCAN);
            break;
        case CommsStates::CONNECTED:
            DiscoveredDevices.clear();
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::CONNECTED);
            break;
        case CommsStates::CONNECTING:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::CONNECTING);
            break;
        case CommsStates::CONNECTION_TIMEOUT:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::CONNECTION_TIMEOUT);
            break;
        case CommsStates::DISCONNECTING:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::DISCONNECTING);
            break;
        case CommsStates::DISCONNECTED:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::DISCONNECTED);
            break;
        case CommsStates::POWERED_OFF:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::POWERED_OFF);
            break;
        case CommsStates::POWERED_ON:
            notify_Machine_Comms->commsStateChanged(MachineCommsStates::POWERED_ON);
            break;
        default :
            break;
    }
    }

   void MachineCommunicationEngine::newDeviceDiscovered(string DeviceID) {

       Device device;
       UUID _UUID;
        device.Name  = DeviceID;
        device.UUID = _UUID.stringValue;
    DiscoveredDevices.push_back(device);

    Machine NewMachine;
    NewMachine.Name = device.Name;
    NewMachine.ID = device.UUID;

    notify_Machine_Comms->newMachineFound( NewMachine);
    }

    void MachineCommunicationEngine::runCommandLoop()
    {
        if(CurrentCommandLoopState != CommandLoopStates::NA){
            CommandLoop_Trigger();
        }
        else
        {
             //printf("NA\n");
        }
        
    }

        void MachineCommunicationEngine::CommandLoop_Trigger()  {
            StringX stringX;
        switch(CurrentCommandLoopState)
        {

            case SendCommand:
                {
                     
                    if(_currentCommsRequestContext.Data.size() > _currentCommsRequestContext.KineticsRequestIndex)
                    {
                        _currentCommsRequestContext.KineticsRequestIndex = _currentCommsRequestContext.KineticsRequestIndex + 1;
                        CurrentCommandLoopState = CommandLoopStates::RecieveData;
                        _currentCommsRequestContext.CurrentResponse = "";
                        CommandLabels::CommandTypes::etype ComamndType = _currentCommsRequestContext.Data.at(_currentCommsRequestContext.KineticsRequestIndex - 1).RequestType;


                        _currentCommsRequestContext.CurrenCommandResponseDataCount = CommandHelper.GetResponseCountForCommand(ComamndType);

                        if(_currentCommsRequestContext.CurrenCommandResponseDataCount > 0)
                        {
                            kineticsResponseTimeoutTimer.stop();
                            kineticsResponseTimeoutTimer = Timer();
                            kineticsResponseTimeoutTimer.setTimeout([&]() {
                                                        KineticsResponseTimeout();
                                                    } , 4000);
                        }

                    // Log("Tx : "+_currentCommsRequestContext.Data[_currentCommsRequestContext.KineticsRequestIndex - 1].Request)

                        KineticsRequest request = _currentCommsRequestContext.Data.at(_currentCommsRequestContext.KineticsRequestIndex - 1);
                        printf(request.Request.c_str());
                        printf("\n");
                        HD_Comms.SendString(request.Request);

                        notify_Machine_Comms->RequestSent(request);
                    }
                    else
                    {

                        kineticsResponseTimeoutTimer.stop();
                            
                   
                        CurrentCommandLoopState = CommandLoopStates::NA;

                        UUID Final_Ack = _currentCommsRequestContext.Acknowlegment_Key;
                        vector<std::unique_ptr<KineticsResponse>> Final_Response;
                        for(int i=0; i<_currentCommsRequestContext.ResponseData.size(); i++)
                        {
                            Final_Response.push_back(std::move(_currentCommsRequestContext.ResponseData.at(i)));
                        }

                        if(CommandBuffer.size() > 0)
                        {
                            vector<KineticsRequest> NextData = CommandBuffer.at(0).Command;
                            UUID NextAcknowledgementKey = CommandBuffer.at(0).AcknowledgementKey;
                            CommandBuffer.erase(CommandBuffer.begin());
                            StartNextCommandTransmission(NextData,  NextAcknowledgementKey);

                        }
                        else
                        {
                            _currentCommsRequestContext.IsCurrentCommandProcessingCompleted  = true;
                        }
                        

                        if(notify_Machine_Comms != nullptr)
                        {
                            notify_Machine_Comms->RecievedResponseData(std::move(Final_Response), Final_Ack);
                        }
                    }
                    break;
                }
            case RecieveData:
                {
                   
                    _currentCommsRequestContext.CurrentResponse = _currentCommsRequestContext.CurrentResponse + _commsDataRecievingContext.NewDataRecieved;
                    _commsDataRecievingContext.NewDataRecieved = "";

                    if(_currentCommsRequestContext.CurrentResponse.back() == ':')
                    {
                        kineticsResponseTimeoutTimer.stop();
                    

                        vector<string> Responses = stringX.split(stringX.removeEnd(_currentCommsRequestContext.CurrentResponse, ':'), ':');
                        int NumberOfResponses = Responses.size();


                        if(NumberOfResponses == _currentCommsRequestContext.CurrenCommandResponseDataCount)
                        {
                            //printf("Rx : "+_currentCommsRequestContext.CurrentResponse)
                            CurrentCommandLoopState = CommandLoopStates::AppendResponse;

                            CommandLoop_Trigger();
                        }
                        else if (NumberOfResponses < _currentCommsRequestContext.CurrenCommandResponseDataCount)
                        {
                            CurrentCommandLoopState = CommandLoopStates::RecieveData;
                        }

                    }

                    break;
                }
            case AppendResponse:
                {
               
                KineticsResponse kr;
                    auto  fp = kr.GetResponseObject(_currentCommsRequestContext.CurrentResponse);
                    _currentCommsRequestContext.ResponseData.push_back(std::move(fp));
                    auto &kineticsReponse = _currentCommsRequestContext.ResponseData.back();


            CommandLabels::CommandTypes commandtype;
         


                    if(kineticsReponse->ResponseType == CommandLabels::CommandTypes::TRG || kineticsReponse->ResponseType == CommandLabels::CommandTypes::ITRG)
                    {
                        notify_Machine_Comms->ParameterTriggerSuccuss();
                    }

                    CurrentCommandLoopState = SendCommand;

                    CommandLoop_Trigger();

                    break;
                }
            default:
                
                    break;

        }
    }

        //Command is a set of KineticsRequests that will be sent in sequence and whose ackknowledgements will be packed together and sent back
    void MachineCommunicationEngine::StartNextCommandTransmission(vector<KineticsRequest> _Command, UUID _Acknowledgement)
    {
        _currentCommsRequestContext.IsCurrentCommandProcessingCompleted  = false;

        _currentCommsRequestContext.Data =  _Command;
        _currentCommsRequestContext.ResponseData.clear();
        _currentCommsRequestContext.CurrenCommandResponseDataCount = 0;
        _currentCommsRequestContext.CurrentResponse   = "";

        _currentCommsRequestContext.KineticsRequestIndex = 0;
        CurrentCommandLoopState = SendCommand;
        _currentCommsRequestContext.Acknowlegment_Key = _Acknowledgement;
        CommandLoop_Trigger();
    }

    void MachineCommunicationEngine::ClearCurrentTransmissionContext()
    {
        _currentCommsRequestContext.IsCurrentCommandProcessingCompleted = true;
        CommandBuffer.clear();
    }

     UUID MachineCommunicationEngine::SendData(vector<KineticsRequest> _Command, int MaxBuffCount)
    {

        UUID _Acknowledgement;

        if(_Command.size() > 0)
        {
            if(MaxBuffCount > 0)
            {
                while(CommandBuffer.size() > MaxBuffCount)
                {
                    CommandBuffer.erase(CommandBuffer.begin());
                }
            } 

            CommandBuffer.push_back( NewCommandRequest( _Acknowledgement,  _Command));
            printf("buf count:%d", CommandBuffer.size());
            if(_currentCommsRequestContext.IsCurrentCommandProcessingCompleted == true)
            {
                 _currentCommsRequestContext.IsCurrentCommandProcessingCompleted  = false;
                    printf("sent command", CommandBuffer.size());
                vector<KineticsRequest> NextData = CommandBuffer.at(0).Command;
                CommandBuffer.erase(CommandBuffer.begin());
                StartNextCommandTransmission( NextData,  _Acknowledgement);
                return _Acknowledgement;
            }
            else
            {
                return _Acknowledgement;
            }
        }

        return _Acknowledgement;
    }

    UUID MachineCommunicationEngine::SendData(vector<KineticsRequest> _Command)
    {
        UUID _Acknowledgement;
        CommandBuffer.push_back( NewCommandRequest( _Acknowledgement,  _Command));
        if(_currentCommsRequestContext.IsCurrentCommandProcessingCompleted == true)
        {
            vector<KineticsRequest> NextData = CommandBuffer.at(0).Command;
            CommandBuffer.erase(CommandBuffer.begin());
            StartNextCommandTransmission( NextData,  _Acknowledgement);
            return _Acknowledgement;
        }
        else
        {
            return _Acknowledgement;
        }
    }


    void MachineCommunicationEngine::stringRecieved(string Data) 
    {

        printf(Data.c_str());
        printf("\n");
      
        string RecievedData = Data;
       
        if(RecievedData.find("~") != string::npos || _commsDataRecievingContext.IsWaitingForPendingRemoteRequestData)
        {
             
            for(int i=0; i<RecievedData.size();i++)
            {
                char c = RecievedData[i];
                if(c == '~')
                {
                    _commsDataRecievingContext.IsWaitingForPendingRemoteRequestData  =  true;
                }
                else
                if(c == ':' && _commsDataRecievingContext.IsWaitingForPendingRemoteRequestData)
                {
                    _commsDataRecievingContext.IsWaitingForPendingRemoteRequestData  =  false;

                   string request = _commsDataRecievingContext.RemoteRequestData;

                std::unique_ptr<std::thread> dataReadThread =  std::unique_ptr<std::thread>( new std::thread([&,request](){ 
                        RemoteCommandToMachineRequest *convertor = new RemoteCommandToMachineRequest();
                        MachineRequests::etype machineReqType =  convertor->Convert(request);
                        notify_Machine_Comms->RecievedRemoteCommand(machineReqType);
                        }));

                        dataReadThread->join();

                    _commsDataRecievingContext.RemoteRequestData = "";
                }
                else
                if(_commsDataRecievingContext.IsWaitingForPendingRemoteRequestData)
                {
                    _commsDataRecievingContext.RemoteRequestData = _commsDataRecievingContext.RemoteRequestData + (c);
                }
                else
                {
                    _commsDataRecievingContext.NewDataRecieved = _commsDataRecievingContext.NewDataRecieved + (c);
                }
            }

            if(_commsDataRecievingContext.IsWaitingForPendingRemoteRequestData == false)
            {
                if(_commsDataRecievingContext.NewDataRecieved != "")
                {
                    runCommandLoop();
                }
            }
        }
        else
        {
            
            _commsDataRecievingContext.NewDataRecieved = RecievedData;
           
            runCommandLoop();

        }



    }


}