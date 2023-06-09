#include <memory>


#include "DB_Local_Store.h"
#include "DataTypes/Servo_Calibration_Type.h"

#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttachLockServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttachServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttentionOff.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttentionOn.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLOne.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLThree.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLTwo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestConnectPower.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDamp.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDelay.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDettachLockServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDettachServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDisconnectPower.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEEPROMRead.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestForActuator.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestFrequency.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestInstantTrigger.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLEEPROMRead.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLRead.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLWrite.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestLeftLockServoAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestLockPowerStatus.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestLockSignalStatus.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOff.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOffLockServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOnLockServo.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestProximityRead.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestRightLockServoAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoDegree.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEEPROMRead.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoMotionCheck.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoPowerStatus.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoSignalStatus.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTrigger.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestVelocity.h"

#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttachLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttachServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOff.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOn.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLOne.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLThree.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLTwo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseConnectPower.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDamp.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDelay.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDettachLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDettachServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDisconnectPower.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEasingInOut.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseFrequency.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseInstantTrigger.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLeftServoAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLockPowerStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLockSignalStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOff.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOffLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOnLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseProximityRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseRightServoAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoDegree.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEasing.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoMotionCheck.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoPowerStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoSignalStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTiming.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTrigger.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseVelocity.h"

#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"

#include "Framework/DataTypes/Constants/ProximityStateSymbols.h"
#include "Framework/DataTypes/Constants/ActuatorSignalStatusSymbols.h"
#include "Framework/DataTypes/Constants/ActuatorPowerStatusSymbols.h"
#include "Framework/DataTypes/Constants/ActuatorMotionSymbols.h"

#include "FrameworkImplementation/KineticsAccess.h"

using namespace fmDB;

namespace fmKinetics
{

std::shared_ptr<KineticsAccess> KineticsAccess::Instance;

void KineticsAccess::RequestSent(KineticsRequest request)
{  if(notify_KineticsParameterUpdates != nullptr)
    {
        notify_KineticsParameterUpdates->ParameterUpdated(request);
    }
}

void KineticsAccess::ParameterTriggerSuccuss()
{  if(notify_KineticsParameterUpdates != nullptr)
    {
        notify_KineticsParameterUpdates->ParametersSetSuccessfully();
    }
}

void KineticsAccess::KineticsResponseDataTimeout(UUID uuid, vector<std::unique_ptr<KineticsResponse>> PartialResponse)
{  if(notify_KineticsResponse != nullptr)
    {
        notify_KineticsResponse->MachiResponseTimeout(std::move(PartialResponse), uuid);
    }
}

void KineticsAccess::RecievedResponseData(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement)
{
    if(notify_KineticsResponse != nullptr)
    {
        notify_KineticsResponse->MachineResponseRecieved(std::move(responeData), _Acknowledgement);
    }
}

void KineticsAccess::commsStateChanged(MachineCommsStates::etype State)
{

    if (State != MachineCommsStates::CONNECTED)
    {
         if(notify_KineticsResponse != nullptr)
    {
        notify_KineticsResponse->CommsLost();
    }
    }

         if(notify_KineticsComms != nullptr)
    {
    notify_KineticsComms->commsStateChanged(State);
    }
}

void KineticsAccess::newMachineFound(Machine Device)
{
     if(notify_KineticsComms != nullptr)
    {
        notify_KineticsComms->newMachineFound(Device);
    }
}

void KineticsAccess::RecievedRemoteCommand(MachineRequests::etype event)
{
     if(notify_KineticsRemoteRequest != nullptr)
    {
        notify_KineticsRemoteRequest->machineRequested(event);
    }
}

UUID KineticsAccess::IndicateAttention()
{
    KineticsRequestAttentionOn request;
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::IndicateNoAttention()
{
    KineticsRequestAttentionOff request;
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadDegree(Actuator::etype actuator)
{
    KineticsRequestServoDegree request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadProximity()
{
    KineticsRequestProximityRead request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadMotionState(Actuator::etype actuatorType)
{
    KineticsRequestServoMotionCheck request(actuatorType);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadActuatorPowerStatus(Actuator::etype actuator)
{

    KineticsRequestServoPowerStatus request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadActuatorSignalStatus(Actuator::etype actuator)
{

    KineticsRequestServoSignalStatus request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadLockPowerStatus()
{

    KineticsRequestLockPowerStatus request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadLockSignalStatus()
{

    KineticsRequestLockSignalStatus request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::PowerOnMotor(Actuator::etype actuator)
{

    KineticsRequestConnectPower request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);

    return ACK;
}

UUID KineticsAccess::PowerOffMotor(Actuator::etype actuator)
{

    KineticsRequestDisconnectPower request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::AttachSignalToActuator(Actuator::etype actuator)
{

    KineticsRequestAttachServo request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::DetachSignalToActuator(Actuator::etype actuator)
{

    KineticsRequestDettachServo request(actuator);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::PowerOnLockMotor()
{

    KineticsRequestPowerOnLockServo request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::PowerOffLockMotor()
{

    KineticsRequestPowerOffLockServo request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::AttachSignalToALockctuator()
{

    KineticsRequestAttachLockServo request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::DetachSignalToLockActuator()
{

    KineticsRequestDettachLockServo request(Actuator::TILT);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::StartInstantMotion()
{
    KineticsRequestInstantTrigger request;
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::StartMotion()
{
    KineticsRequestTrigger request;
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

bool KineticsAccess::CheckProximity(vector<std::unique_ptr<KineticsResponse>> response)
{

    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::PRX)
    {
        KineticsResponseProximityRead *ProximityResponse = (KineticsResponseProximityRead*)(response.at(0).get());

        if (ProximityResponse != nullptr && ProximityResponse->MountState == ProximityStateSymbols::MOUNTED)
        {
            return true;
        }
    }
    return false;
}

bool KineticsAccess::CheckActuatorPowerStatus(vector<std::unique_ptr<KineticsResponse>> response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::SPW)
    {
        KineticsResponseServoPowerStatus *PowerStatusResponse = (KineticsResponseServoPowerStatus*)(response.at(0).get());

        if (PowerStatusResponse != nullptr && PowerStatusResponse->PowerState == ActuatorPowerStatusSymbols::ON)
        {
            return true;
        }
    }
    return false;
}

bool KineticsAccess::CheckActuatorSignalStatus(vector<std::unique_ptr<KineticsResponse>> response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::SAT)
    {
        KineticsResponseServoSignalStatus *SignalStatusResponse = (KineticsResponseServoSignalStatus*)(response.at(0).get());

        if (SignalStatusResponse != nullptr && SignalStatusResponse->SignalState == ActuatorSignalStatusSymbols::ATTACHED)
        {
            return true;
        }
    }
    return false;
}

bool KineticsAccess::CheckLockPowerStatus(vector<std::unique_ptr<KineticsResponse>> response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::LPW)
    {
        KineticsResponseLockPowerStatus *LockPowerStatusResponse = (KineticsResponseLockPowerStatus*)(response.at(0).get());

        if (LockPowerStatusResponse != nullptr && LockPowerStatusResponse->PowerState == ActuatorPowerStatusSymbols::ON)
        {
            return true;
        }
    }
    return false;
}

bool KineticsAccess::CheckLockSignalStatus(vector<std::unique_ptr<KineticsResponse>> response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::LAT)
    {
        KineticsResponseLockSignalStatus *LockSignalStatusResponse = (KineticsResponseLockSignalStatus*)(response.at(0).get());

        if (LockSignalStatusResponse != nullptr && LockSignalStatusResponse->SignalState == ActuatorSignalStatusSymbols::ATTACHED)
        {
            return true;
        }
    }
    return false;
}

UUID KineticsAccess::ReadActuatorAddress(Actuator::etype actuator)
{
    KineticsEEPROM kineticsEEPROM;
    KineticsRequestEEPROMRead request(*kineticsEEPROM.MEMORY_MAP.at(MachineConfig::Instance.MachineActuatorList.at(actuator)->ActuatorAddressLocationInEERPOM));
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

bool KineticsAccess::SetActuatorAddress(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>>  response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::EEPR)
    {
        KineticsResponseEEPROMRead *EEPROMRead = (KineticsResponseEEPROMRead*)(response.at(0).get());
        if (EEPROMRead != nullptr && EEPROMRead->ResponseType == CommandLabels::CommandTypes::EEPR && EEPROMRead->Data.size() > 0)
        {
            MachineConfig::Instance.MachineActuatorList.at(actuator)->Address = EEPROMRead->Data.at(0);
            return true;
        }
    }

    return false;
}

UUID KineticsAccess::ReadDeltaResetAngle(Actuator::etype actuator)
{
    KineticsRequestEEPROMRead request(*KineticsEEPROM().MEMORY_MAP.at(MachineConfig::Instance.MachineActuatorList.at(actuator)->ShutdownAngleAddressLocationInEERPOM));
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

bool KineticsAccess::SetDeltaResetAngle(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>>  response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::EEPR)
    {
        KineticsResponseEEPROMRead *EEPROMRead = (KineticsResponseEEPROMRead *)(response.at(0).get());
        if (EEPROMRead != nullptr && EEPROMRead->ResponseType == CommandLabels::CommandTypes::EEPR && EEPROMRead->Data.size() > 0)
        {
            MachineConfig::Instance.MachineActuatorList.at(actuator)->ShutdownDeltaAngle = EEPROMRead->Data.at(0);
            if (EEPROMRead->Data.at(1) == 1)
            {
                MachineConfig::Instance.MachineActuatorList.at(actuator)->ShutdownDeltaAngle = MachineConfig::Instance.MachineActuatorList.at(actuator)->ShutdownDeltaAngle * -1;
            }
            return true;
        }
    }
    return false;
}

UUID KineticsAccess::ReadReferanceAngle(Actuator::etype actuator)
{
    KineticsRequestEEPROMRead request(*KineticsEEPROM().MEMORY_MAP.at(MachineConfig::Instance.MachineActuatorList.at(actuator)->RefAngleAddressLocationInEERPOM));
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

bool KineticsAccess::SetReferanceAngle(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>>  response)
{
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::EEPR)
    {
        KineticsResponseEEPROMRead *EEPROMRead = (KineticsResponseEEPROMRead *)(response.at(0).get());
        if (EEPROMRead != nullptr && EEPROMRead->ResponseType == CommandLabels::CommandTypes::EEPR && EEPROMRead->Data.size() > 0)
        {
            MachineConfig::Instance.MachineActuatorList.at(actuator)->RefPosition = EEPROMRead->Data.at(0);
            return true;
        }
    }

    return false;
}

KineticsRequestAngle KineticsAccess::GetKineticRequestAngleFromDegreeResponse(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>> response)
{
    DB_Local_Store db;
    KineticsRequestAngle request("");
    if (response.size() == 1 && response.at(0)->ResponseType == CommandLabels::CommandTypes::DEG)
    {
        KineticsResponseServoDegree *ADCRead = (KineticsResponseServoDegree *)(response.at(0).get());

        int Degree = db.GetServoDegreeFromADC((MachineConfig::Instance.MachineActuatorList.at(actuator)->CalibrationStoreName), ADCRead->ADC);
        if (Degree == -1)
        {
            return request;
        }
        request = KineticsRequestAngle((Degree), actuator);
        return request;
    }

    return request;
}

int KineticsAccess::GetDeltaAngleFromFullAngle(int FullAngle, Actuator::etype actuator)
{
    return (FullAngle - (MachineConfig::Instance.MachineActuatorList.at(actuator)->RefPosition));
}

int KineticsAccess::GetFullAngleFromDeltaAngle(int DeltaAngle, Actuator::etype actuator)
{
    return (DeltaAngle + (MachineConfig::Instance.MachineActuatorList.at(actuator)->RefPosition));
}

vector<KineticsRequest> KineticsAccess::GetPredefinedKineticsRequestAngleByName(string Name)
{
    DB_Local_Store db;
    Machine_Position_Type Command = db.ReadMachinePositionByName(Name);
    vector<KineticsRequest> kineticsRequests;
    if (Command.Name.compare(Name) == 0)
    {

        int FullTurnAngle = (Command.TURN) + (MachineConfig::Instance.MachineActuatorList.at(Actuator::TURN)->RefPosition);
        kineticsRequests.push_back(KineticsRequestAngle(FullTurnAngle, Actuator::TURN));

        int FullLiftAngle = (Command.LIFT) + (MachineConfig::Instance.MachineActuatorList.at(Actuator::LIFT)->RefPosition);
        kineticsRequests.push_back(KineticsRequestAngle(FullLiftAngle, Actuator::LIFT));

        int FullLeanAngle = (Command.LEAN) + (MachineConfig::Instance.MachineActuatorList.at(Actuator::LEAN)->RefPosition);
        kineticsRequests.push_back(KineticsRequestAngle(FullLeanAngle, Actuator::LEAN));

        int FullTiltAngle = (Command.TILT) + (MachineConfig::Instance.MachineActuatorList.at(Actuator::TILT)->RefPosition);
        kineticsRequests.push_back(KineticsRequestAngle(FullTiltAngle, Actuator::TILT));
    }
    return kineticsRequests;
}

UUID KineticsAccess::SetParameters(vector<KineticsRequest> parameters)
{
    UUID ACK = machineComms->SendData(parameters);
    return ACK;
}

UUID KineticsAccess::SetGameEffectParameters(vector<KineticsRequest> parameters)
{
    UUID ACK = machineComms->SendData(parameters, 1);
    return ACK;
}

//Manadatory call to make the Machine Communication system ready
void KineticsAccess::SetCommsDelegate(std::shared_ptr<KineticsCommsConvey> delegate)
{
    notify_KineticsComms = delegate;

    //Set BT comms Delegates first time this method is called
    //This will be set only once, every time the is application run
    if (!IsCommsDelegatesInitialized)
    {
        IsCommsDelegatesInitialized = true;
        std::shared_ptr<MachineCommsConvey> m_MachineCommsConvey{getPtr()};
        machineComms->SetCommsDelegate(m_MachineCommsConvey);
    }
}
void KineticsAccess::InitializeComms()
{
    machineComms->InitializeComms();
}

//Start scanning of machines
void KineticsAccess::StartScan()
{
    //machineComms.StartScan();
}

//Stops scanning for machines
void KineticsAccess::StopScan()
{
    //machineComms.StopScan();
}

void KineticsAccess::ConnectToMachine(Machine machine)
{
    //machineComms.ConnectToMachine(machine);
}

bool KineticsAccess::IsConnectedToMachine()
{
    return machineComms->IsConnectedToMachine();
}

void KineticsAccess::DisconnectMachine()
{
    machineComms->DisconnectMachine();
}

void KineticsAccess::SetMachineRemoteRequestListener(std::shared_ptr<KineticsRemoteRequestConvey> delegate)
{
    notify_KineticsRemoteRequest = delegate;
}

void KineticsAccess::SetKineticsResposeListener(std::shared_ptr<KineticsResponseConvey> delegate)
{
    notify_KineticsResponse = delegate;
}

void KineticsAccess::SetKineticsParameterUpdatesListener(std::shared_ptr<KineticsParameterUpdatesConvey> delegate)
{
    notify_KineticsParameterUpdates = delegate;
}

void KineticsAccess::ResetCommsContext()
{
    machineComms->ClearCurrentTransmissionContext();
}

UUID KineticsAccess::TurnOffPower()
{
    KineticsRequestPowerOff request;
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::WriteToEEPROM(EEPROMDetails AddressDetails, int Data)
{
    KineticsRequestEEPROMWrite request(AddressDetails, Data);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

UUID KineticsAccess::ReadFromEEPROM(EEPROMDetails AddressDetails)
{
    KineticsRequestEEPROMRead request(AddressDetails);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

vector<int> KineticsAccess::ExtractBytesFromEEPROMReadResponse(KineticsResponse EEPROMReadResponse)
{
    if (EEPROMReadResponse.ResponseType == CommandLabels::CommandTypes::EEPR)
    {
        KineticsResponseEEPROMRead *readResponse = dynamic_cast<KineticsResponseEEPROMRead *>(&EEPROMReadResponse);
        if (readResponse != nullptr)
            return readResponse->Data;
        else
            return vector<int>();
    }
    return vector<int>();
}

bool KineticsAccess::CheckWriteToEEPROM(KineticsResponse Response)
{
    if (Response.ResponseType == CommandLabels::CommandTypes::EEPW)
    {
        KineticsResponseEEPROMWrite *EEPROMWrite = dynamic_cast<KineticsResponseEEPROMWrite *>(&Response);
        if (EEPROMWrite != nullptr && EEPROMWrite->ResponseType == CommandLabels::CommandTypes::EEPW && EEPROMWrite->RequestRecievedAck == KineticsResponseAcknowledgement::OK)
        {
            return true;
        }
    }

    return false;
}

//read given number of bytes from from Servo board eeprom Address location
UUID KineticsAccess::ReadFromServoEEPROM(Actuator::etype actuator, EEPROMDetails AddressDetails)
{
    KineticsRequestServoEEPROMRead request(actuator, AddressDetails);
    vector<KineticsRequest> req{request};
    UUID ACK = machineComms->SendData(req);
    return ACK;
}

//Returns the payload bytes from ServoEEPROMReadResonse Command
vector<int> KineticsAccess::ExtractBytesFromServoEEPROMReadResponse(KineticsResponse EEPROMReadResponse)
{
    if (EEPROMReadResponse.ResponseType == CommandLabels::CommandTypes::SEPR)
    {
        KineticsResponseServoEEPROMRead *readResponse = dynamic_cast<KineticsResponseServoEEPROMRead *>(&EEPROMReadResponse);
        if (readResponse != nullptr)
            return readResponse->Data;
        else
            return vector<int>();
    }
    return vector<int>();
}

void KineticsAccess::DeleteCalibrationDataForActuator(Actuator::etype actuator)
{
    DB_Local_Store db;
    db._EmptyTable(DB_Table_Columns().toString.at(MachineConfig::Instance.MachineActuatorList.at(actuator)->CalibrationStoreName));
}

void KineticsAccess::SaveActuatorCalibrationData(Actuator::etype actuator, int Degree, int ADC)
{
    Servo_Calibration_Type calibType;
    calibType.Name = MachineConfig::Instance.MachineActuatorList.at(actuator)->CalibrationStoreName;
    calibType.Degree = Degree;
    calibType.ADC = ADC;
    DB_Local_Store db;
    db.saveCalibrationData(calibType);
}
} // namespace fmKinetics