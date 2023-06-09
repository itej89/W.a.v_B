#pragma once 


#include <string>
#include <vector>

#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkInterface/PublicTypes/serial_access.h"
#include "FrameworkInterface/PublicTypes/CommsConvey.h"
#include "FrameworkInterface/PublicTypes/Device.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"
#include "Framework/DataTypes/Delegates/MachineCommsConvey.h"
#include "Framework/DataTypes/Parsers/RemoteCommandToMachineRequest.h"
#include "UUID.h"
#include "Timer.h"
#include "FrameworkInterface/PublicTypes/Constants/CommsStates.h"
#include "Framework/DataTypes/MachineCommandHelper.h"
#include "FrameworkImplementation/PublicTypes/Machine.h"

using std::string;
using std::vector;

using fmCommon::UUID;
using fmCommon::Timer;
using fmCommon::StringX;
using fmSerial::Serial_Access;
using fmSerial::Device;
using fmSerial::CommsStates;
using fmSerial::CommsConvey;

namespace fmKinetics
{
    class MachineCommunicationEngine: public CommsConvey, public std::enable_shared_from_this<MachineCommunicationEngine>{
    public:

    
     std::shared_ptr<MachineCommunicationEngine> getPtr()
     {
         return shared_from_this();
     }


     Timer kineticsResponseTimeoutTimer;

    vector<Device> DiscoveredDevices;

    //Bluetooth Communication interface object
    Serial_Access HD_Comms;
    std::shared_ptr<MachineCommsConvey> notify_Machine_Comms;

    //Contains Parameters to identify the type of the data incoming from the Comms Module
     class CommsDataRecievingContext
    {
         public:
            bool IsWaitingForPendingRemoteRequestData = false;
            string NewDataRecieved = "";
            string RemoteRequestData = "";
    };
    CommsDataRecievingContext _commsDataRecievingContext;


    //This contains the parameters for handling the the list of KineticRequests in the ComamndBuffer at the CommandIndex
     class CurrentCommsRequestContext
    {

        public:
            int CurrenCommandResponseDataCount = 0;

            string CurrentResponse = "";

            vector<KineticsRequest> Data;
           vector<std::unique_ptr<KineticsResponse>> ResponseData;

            UUID Acknowlegment_Key;

            bool IsCurrentCommandProcessingCompleted = true;


            int KineticsRequestIndex = 0;
    };
    CurrentCommsRequestContext _currentCommsRequestContext;;


    class NewCommandRequest
    {
        public:
         UUID AcknowledgementKey;
          vector<KineticsRequest> Command;

         NewCommandRequest(UUID _AcknowledgementKey, vector<KineticsRequest> _Command):  
         AcknowledgementKey(_AcknowledgementKey), Command(_Command){}
    };

    vector<NewCommandRequest> CommandBuffer;


    MachineCommandHelper CommandHelper;



     MachineCommunicationEngine();
     ~MachineCommunicationEngine();

    private:
    void KineticsResponseTimeout();

     //Used when  data send by remote device for a sent command
    void runCommandLoop();



    public:
    //Manadatory call to make the Machine Communication system ready
     void SetCommsDelegate(std::shared_ptr<MachineCommsConvey> delegate);

     void InitializeComms();

     bool IsConnectedToMachine();

     void DisconnectMachine();



     void serialStataChanged(CommsStates State);

     void newDeviceDiscovered(string DeviceID);



    enum CommandLoopStates {
         NA,
         SendCommand,
         RecieveData,
         AppendResponse
    };

    CommandLoopStates CurrentCommandLoopState = CommandLoopStates::NA;

    void CommandLoop_Trigger();

    //Command is a set of KineticsRequests that will be sent in sequence and whose acknowledgements will be packed together and sent back
    void StartNextCommandTransmission(vector<KineticsRequest> _Command, UUID _Acknowledgement);

    void ClearCurrentTransmissionContext();


    UUID SendData(vector<KineticsRequest> _Command);

    UUID SendData(vector<KineticsRequest> _Command, int MaxBuffCount);

    void stringRecieved(string Data);

    };
}