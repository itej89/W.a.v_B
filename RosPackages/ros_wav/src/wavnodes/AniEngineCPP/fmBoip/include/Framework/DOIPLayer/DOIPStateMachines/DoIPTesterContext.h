#pragma once

#include <stdint-gcc.h>
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <vector>

#include "ThreadX.h"


#include "Framework/Validation/interface/IValidation.h"
#include "Framework/DOIPLayer/DoIPGenericHeaderHandler.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DOIPLayer/DOIPStateMachines/Interface/IDiagState.h"

#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/VehicleIdentificationDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/RoutingActivationDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagnosticMessagesDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagMessageNAKDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagMessagePosACKDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/GenericHeaderNAKDiagState.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/AliveCheckDiagState.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/TESTER_CODE_VALUES/Vehicle_Identification_Types.h"
#include "Framework/TransportLayer/Helpers/RecievedData.h"
#include "Framework/DataTypes/Extras/TransportClientConvey.h"
#include "Framework/DataTypes/Extras/DOIPContextConvey.h"
#include "Framework/DataTypes/Extras/DOIPContextResultConvey.h"


namespace fmBoip
{
    class DoIPTesterContext : public TransportClientConvey
    {
   
    public:
        fmCommon::ThreadX DOIPFrameListener;
        std::shared_ptr<fmCommon::ThreadX> DOIPFrameSender;

        std::map<Response_Payload_Types::CODE, std::shared_ptr<IDiagState>> payloadType_DiagState = {
            { Response_Payload_Types::PLD_VEH_IDEN_RES, std::make_shared<VehicleIdentificationDiagState>()},
            { Response_Payload_Types::PLD_ROUTING_ACTIVATION_RES, std::make_shared<RoutingActivationDiagState>()},
            { Response_Payload_Types::PLD_DIAG_MESSAGE, std::make_shared<DiagnosticMessagesDiagState>()},
            { Response_Payload_Types::PLD_DIAG_MESSAGE_NEGATIVE_ACK, std::make_shared<DiagMessageNAKDiagState>()},
            { Response_Payload_Types::PLD_DIAG_MESSAGE_POSITIVE_ACK, std::make_shared<DiagMessagePosACKDiagState>()},
            { Response_Payload_Types::PLD_DOIP_HEADER_NAK, std::make_shared<GenericHeaderNAKDiagState>()},
            { Response_Payload_Types::PLD_ALIVE_CHECK_REQ, std::make_shared<AliveCheckDiagState>()}
        //    { Response_Payload_Types::PLD_DIAG_POWER_MODE_RES, DiagPowerModeDiagState()},
        //    { Response_Payload_Types::PLD_DOIP_ENTITY_STATUS_RES, DoIPEntityStatusDiagState()},
        };

        std::map<Vehicle_Identification_Types::CODE, std::shared_ptr<IDiagState>>  identificationType_DiagState = {
            {Vehicle_Identification_Types::VEHICLE_IDENTIFICATION, std::make_shared<VehicleIdentificationDiagState>()},
            // {Vehicle_Identification_Types::VEHICLE_IDENTIFICATION_EID:VehicleIdentificationWithEIDDiagState()},
            // {Vehicle_Identification_Types::VEHICLE_IDENTIFICATION_VIN:VehicleIdentificationWithVINDiagState()},
        };
        
        
        bool IsVehicleIdentificationResponseRecieved = false;
        
        bool StopRoutingActivationLoop = true;
        bool RoutingActivationLoopStopped = true;
        bool RoutingActivationLoopStarted = false;
        
        
        bool StopDataParsingLoop = true;
        bool DataParsingStopped = true;
        bool DataParsingStarted = false;
        

        IDiagState* _currentState;
        IDiagState* getCurrentState();
        void setCurrentState(IDiagState* newState);
        
        IDiagState*  _previousState;
        IDiagState* getPreviousState();
        void setPreviousState(IDiagState* oldState);
        
        
        std::vector<RecievedData> TCPDataBuffer;
        std::vector<std::pair<bool, DOIPResponseObject>> DOIPBuffer;
        std::pair<bool, std::vector<uint8_t>> DOIPFrameBuffer;

        DOIPContextConvey* ContextConvey;
        DOIPContextResultConvey* ResultConvey;


        DoIPTesterContext();


        //DOIP Communication Initializing sequence
        int _Initialize(DOIPContextConvey* _ContextConvey, DOIPContextResultConvey* _ResultConvey);
        
        void _UnInitialize();

        int MoveNext(std::vector<uint8_t> dataToBeSent);

        void FinalizeDiag();


        void ParseTCPData(RecievedData recData);

        
        int AnnounceDiscover();
        
        int RoutingActivation(DOIPEntity Entity);
        

        void HandleIncomingData(DOIPResponseObject data);
        
        void HandleDiagnostic(DOIPResponseObject objResponse);
        
        void HandleDiagAcknowledgement(DOIPResponseObject data);
        


        void ReadDOIPFrame();

        void StartDataParserLoop();
        
        void SendDOIPFrameOverTCP();

        void StartDOIPSendLoop();
        


        int SendData(std::vector<uint8_t> Data);
        
        int SendUDSRequest(std::vector<uint8_t> dataToBeSent);



        //TransportClientConvey
        void Disconnected();

        void DataRecieved(RecievedData recievedData);
        
        void Timeout(int code);
        //End of TransportClientConvey

        ~DoIPTesterContext();
};

}