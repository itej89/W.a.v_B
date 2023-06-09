
#include <memory>
#include <iostream>

#include "DB_Local_Store.h"
#include "DataTypes/Expressions_Type.h"

#include "nlohmann/json.hpp"

#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDelay.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTrigger.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestInstantTrigger.h"

#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"

#include "AnimationObject.h"
#include "AnimationPositions.h"
#include "MotorAnimationState.h"
#include "MotionAnimationTransition.h"

#include "Initialization/BindJOB/MachineBindJOB.h"

using namespace fmDB;
using jsonObject = nlohmann::json;
using namespace fmKinetics;
using namespace fmMotionData;

namespace fmSystem
{



std::shared_ptr<MachineBindJOB> MachineBindJOB::getPtr()
{
    return shared_from_this();
}

void MachineBindJOB::SetBindStatusConvey(std::shared_ptr<MachineBindStatusDelegate> delegate)
{
    BindStateConvey = delegate;
}

//KineticsResponseConvey
void MachineBindJOB::CommsLost() {}
void MachineBindJOB::MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement)
{
    DOSTEP();
}
void MachineBindJOB::MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement)
{
    if (_Acknowledgement.stringValue.compare(WaitingForKineticsRequestAck.stringValue) == 0)
    {
        WaitingForKineticsRequestAck = UUID();
        LastKineticsResponse = std::move(responeData);
        DOSTEP();
    }
}
//End of KineticsResponseConvey

//Scheduler Calls
void MachineBindJOB::TakeOverResources()
{

    KineticsAccess::getInstance()->SetKineticsResposeListener(getPtr());
}
void MachineBindJOB::Resume()
{
    DOSTEP();
}
void MachineBindJOB::Pause()
{
    KineticsAccess::getInstance()->SetKineticsResposeListener(nullptr);
    KineticsAccess::getInstance()->ResetCommsContext();
}
//End Of Scheduler calls

void MachineBindJOB::BindActuatorSignal()
{
    MachineBindActuators = true;
    CURRENT_STATE = BIND_STATES::PING;
    DOSTEP();
}

void MachineBindJOB::DOSTEP()
{
    switch (CURRENT_STATE)
    {
    case BIND_STATES::PING:
        CURRENT_STATE = BIND_STATES::VALIDATE_PING;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->StartInstantMotion();
        break;

    case BIND_STATES::VALIDATE_PING:
        if (LastKineticsResponse.size() == 1 && LastKineticsResponse.at(0)->ResponseType == CommandLabels::CommandTypes::ITRG)
        {
            CURRENT_STATE = BIND_STATES::READ_TURN_ADR;
            Resume();
        }
        break;

    case BIND_STATES::READ_TURN_ADR:
        CURRENT_STATE = BIND_STATES::SET_TURN_ADR;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorAddress(Actuator::TURN);
        break;

    case BIND_STATES::SET_TURN_ADR:
        CURRENT_STATE = BIND_STATES::READ_LIFT_ADR;
        if (KineticsAccess::getInstance()->SetActuatorAddress(Actuator::TURN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LIFT_ADR:
        CURRENT_STATE = BIND_STATES::SET_LIFT_ADR;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorAddress(Actuator::LIFT);
        break;

    case BIND_STATES::SET_LIFT_ADR:
        CURRENT_STATE = BIND_STATES::READ_LEAN_ADR;
        if (KineticsAccess::getInstance()->SetActuatorAddress(Actuator::LIFT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LEAN_ADR:
        CURRENT_STATE = BIND_STATES::SET_LEAN_ADR;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorAddress(Actuator::LEAN);
        break;

    case BIND_STATES::SET_LEAN_ADR:
        CURRENT_STATE = BIND_STATES::READ_TILT_ADR;
        if (KineticsAccess::getInstance()->SetActuatorAddress(Actuator::LEAN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_TILT_ADR:
        CURRENT_STATE = BIND_STATES::SET_TILT_ADR;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorAddress(Actuator::TILT);
        break;

    case BIND_STATES::SET_TILT_ADR:
        CURRENT_STATE = BIND_STATES::READ_TURN_REF;
        if (KineticsAccess::getInstance()->SetActuatorAddress(Actuator::TILT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_TURN_REF:
        CURRENT_STATE = BIND_STATES::SET_TURN_REF;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadReferanceAngle(Actuator::TURN);
        break;

    case BIND_STATES::SET_TURN_REF:
        CURRENT_STATE = BIND_STATES::READ_LIFT_REF;
        if (KineticsAccess::getInstance()->SetReferanceAngle(Actuator::TURN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LIFT_REF:
        CURRENT_STATE = BIND_STATES::SET_LIFT_REF;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadReferanceAngle(Actuator::LIFT);
        break;

    case BIND_STATES::SET_LIFT_REF:
        CURRENT_STATE = BIND_STATES::READ_LEAN_REF;
        if (KineticsAccess::getInstance()->SetReferanceAngle(Actuator::LIFT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LEAN_REF:
        CURRENT_STATE = BIND_STATES::SET_LEAN_REF;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadReferanceAngle(Actuator::LEAN);
        break;

    case BIND_STATES::SET_LEAN_REF:
        CURRENT_STATE = BIND_STATES::READ_TILT_REF;
        if (KineticsAccess::getInstance()->SetReferanceAngle(Actuator::LEAN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_TILT_REF:
        CURRENT_STATE = BIND_STATES::SET_TILT_REF;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadReferanceAngle(Actuator::TILT);
        break;

    case BIND_STATES::SET_TILT_REF:
        CURRENT_STATE = BIND_STATES::READ_TURN_DELTA_ANGLE;
        if (KineticsAccess::getInstance()->SetReferanceAngle(Actuator::TILT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_TURN_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::SET_TURN_DELTA_ANGLE;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDeltaResetAngle(Actuator::TURN);
        break;

    case BIND_STATES::SET_TURN_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::READ_LIFT_DELTA_ANGLE;
        if (KineticsAccess::getInstance()->SetDeltaResetAngle(Actuator::TURN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LIFT_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::SET_LIFT_DELTA_ANGLE;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDeltaResetAngle(Actuator::LIFT);
        break;

    case BIND_STATES::SET_LIFT_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::READ_LEAN_DELTA_ANGLE;
        if (KineticsAccess::getInstance()->SetDeltaResetAngle(Actuator::LIFT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_LEAN_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::SET_LEAN_DELTA_ANGLE;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDeltaResetAngle(Actuator::LEAN);
        break;

    case BIND_STATES::SET_LEAN_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::READ_TILT_DELTA_ANGLE;
        if (KineticsAccess::getInstance()->SetDeltaResetAngle(Actuator::LEAN, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::READ_TILT_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::SET_TILT_DELTA_ANGLE;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDeltaResetAngle(Actuator::TILT);
        break;

    case BIND_STATES::SET_TILT_DELTA_ANGLE:
        CURRENT_STATE = BIND_STATES::DETACH_TURN;
        if (KineticsAccess::getInstance()->SetDeltaResetAngle(Actuator::TILT, std::move(LastKineticsResponse)))
        {
            Resume();
        }
        break;

    case BIND_STATES::DETACH_TURN:
        CURRENT_STATE = BIND_STATES::DETACH_LEAN;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->DetachSignalToActuator(Actuator::TURN);
        break;

    case BIND_STATES::DETACH_LEAN:
        CURRENT_STATE = BIND_STATES::DETACH_LIFT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->DetachSignalToActuator(Actuator::LEAN);
        break;

    case BIND_STATES::DETACH_LIFT:
        CURRENT_STATE = BIND_STATES::DETACH_TILT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->DetachSignalToActuator(Actuator::LIFT);
        break;

    case BIND_STATES::DETACH_TILT:
        CURRENT_STATE = BIND_STATES::IS_TURN_CONNECTED;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->DetachSignalToActuator(Actuator::TILT);
        break;

    case BIND_STATES::IS_TURN_CONNECTED:
    {

        if (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::TURN) != BindedActuatorList.end())
        {

            CURRENT_STATE = BIND_STATES::IS_LEAN_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::CONNECT_TURN;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorPowerStatus(Actuator::TURN);
        }

        break;
    }

    case BIND_STATES::CONNECT_TURN:
    {
        if (KineticsAccess::getInstance()->CheckActuatorPowerStatus(std::move(LastKineticsResponse)))
        {
            CURRENT_STATE = BIND_STATES::IS_TURN_ATTACHED;
            Resume();
        }
        else
        {

            CURRENT_STATE = BIND_STATES::IS_TURN_ATTACHED;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOnMotor(Actuator::TURN);
        }
        break;
    }

    case BIND_STATES::IS_TURN_ATTACHED:
    {
        CURRENT_STATE = BIND_STATES::DUMMY_READ_DEGREE_TURN;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorSignalStatus(Actuator::TURN);
        break;
    }

    case BIND_STATES::DUMMY_READ_DEGREE_TURN:
    {
        if (KineticsAccess::getInstance()->CheckActuatorSignalStatus(std::move(LastKineticsResponse)))
        {
            KineticsTurnRequest.clear();
            BindedActuatorList.push_back(Actuator::TURN);
            CURRENT_STATE = BIND_STATES::IS_LEAN_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::READ_DEGREE_TURN;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::TURN);
        }
        break;
    }

    case BIND_STATES::READ_DEGREE_TURN:
    {
        KineticsTurnRequest.push_back(KineticsRequestTiming(100, Actuator::TURN));
        KineticsTurnRequest.push_back(KineticsRequestDelay(0, Actuator::TURN));

        CURRENT_STATE = BIND_STATES::SET_DEGREE_TURN;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::TURN);

        break;
    }

    case BIND_STATES::SET_DEGREE_TURN:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_TURN;

        KineticsRequest request = KineticsAccess::getInstance()->GetKineticRequestAngleFromDegreeResponse(Actuator::TURN, std::move(LastKineticsResponse));
        vector<KineticsRequest> req{
            KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::TURN),
            KineticsRequestEasingInOut(CommandLabels::EasingType::IN, Actuator::TURN),
            request};

        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);
        break;
    }

    case BIND_STATES::TRIGGER_TURN:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_TURN_CONFIRM;

        if (KineticsTurnRequest.size() > 0)
        {
            KineticsTurnRequest.push_back(KineticsRequestTrigger());
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(KineticsTurnRequest);
        }
        else
        {
            Resume();
        }

        break;
    }

    case BIND_STATES::TRIGGER_TURN_CONFIRM:
    {
        CURRENT_STATE = BIND_STATES::ATTACH_SERVO_TURN;

        WorkerThread.push_back(std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            try
            {
                /* code */
                vector<KineticsRequest> _TriggerAngles;
                _TriggerAngles.push_back(KineticsRequestTrigger());
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(_TriggerAngles);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }));

        break;
    }

    case BIND_STATES::ATTACH_SERVO_TURN:
    {
        CURRENT_STATE = BIND_STATES::IS_LEAN_CONNECTED;
        if (KineticsTurnRequest.size() > 0)
        {

            if (MachineBindActuators)
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->AttachSignalToActuator(Actuator::TURN);
                BindedActuatorList.push_back(Actuator::TURN);
            }
            else
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOffMotor(Actuator::TURN);
            }
        }
        else
        {
            Resume();
        }
        break;
    }

    case BIND_STATES::IS_LEAN_CONNECTED:
    {

        if (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::LEAN) != BindedActuatorList.end())
        {

            CURRENT_STATE = BIND_STATES::IS_LIFT_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::CONNECT_LEAN;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorPowerStatus(Actuator::LEAN);
        }

        break;
    }

    case BIND_STATES::CONNECT_LEAN:
    {
        if (KineticsAccess::getInstance()->CheckActuatorPowerStatus(std::move(LastKineticsResponse)))
        {
            CURRENT_STATE = BIND_STATES::IS_LEAN_ATTACHED;
            Resume();
        }
        else
        {

            CURRENT_STATE = BIND_STATES::IS_LEAN_ATTACHED;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOnMotor(Actuator::LEAN);
        }
        break;
    }

    case BIND_STATES::IS_LEAN_ATTACHED:
    {
        CURRENT_STATE = BIND_STATES::DUMMY_READ_DEGREE_LEAN;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorSignalStatus(Actuator::LEAN);
        break;
    }

    case BIND_STATES::DUMMY_READ_DEGREE_LEAN:
    {
        if (KineticsAccess::getInstance()->CheckActuatorSignalStatus(std::move(LastKineticsResponse)))
        {
            KineticsLeanRequest.clear();
            BindedActuatorList.push_back(Actuator::LEAN);
            CURRENT_STATE = BIND_STATES::IS_LIFT_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::READ_DEGREE_LEAN;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::LEAN);
        }
        break;
    }

    case BIND_STATES::READ_DEGREE_LEAN:
    {
        KineticsLeanRequest.push_back(KineticsRequestTiming(100, Actuator::LEAN));
        KineticsLeanRequest.push_back(KineticsRequestDelay(0, Actuator::LEAN));

        CURRENT_STATE = BIND_STATES::SET_DEGREE_LEAN;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::LEAN);

        break;
    }

    case BIND_STATES::SET_DEGREE_LEAN:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_LEAN;

        KineticsRequest request = KineticsAccess::getInstance()->GetKineticRequestAngleFromDegreeResponse(Actuator::LEAN, std::move(LastKineticsResponse));
        vector<KineticsRequest> req{
            KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LEAN),
            KineticsRequestEasingInOut(CommandLabels::EasingType::IN, Actuator::LEAN),
            request};

        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);
        break;
    }

    case BIND_STATES::TRIGGER_LEAN:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_LEAN_CONFIRM;

        if (KineticsLeanRequest.size() > 0)
        {
            KineticsLeanRequest.push_back(KineticsRequestTrigger());
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(KineticsLeanRequest);
        }
        else
        {
            Resume();
        }

        break;
    }

    case BIND_STATES::TRIGGER_LEAN_CONFIRM:
    {
        CURRENT_STATE = BIND_STATES::ATTACH_SERVO_LEAN;

        WorkerThread.push_back(std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            try
            {
                /* code */
                vector<KineticsRequest> _TriggerAngles;
                _TriggerAngles.push_back(KineticsRequestTrigger());
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(_TriggerAngles);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }));

        break;
    }

    case BIND_STATES::ATTACH_SERVO_LEAN:
    {
        CURRENT_STATE = BIND_STATES::IS_LIFT_CONNECTED;
        if (KineticsLeanRequest.size() > 0)
        {

            if (MachineBindActuators)
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->AttachSignalToActuator(Actuator::LEAN);
                BindedActuatorList.push_back(Actuator::LEAN);
            }
            else
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOffMotor(Actuator::LEAN);
            }
        }
        else
        {
            Resume();
        }
        break;
    }

    case BIND_STATES::IS_LIFT_CONNECTED:
    {

        if (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::LIFT) != BindedActuatorList.end())
        {

            CURRENT_STATE = BIND_STATES::IS_TILT_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::CONNECT_LIFT;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorPowerStatus(Actuator::LIFT);
        }

        break;
    }

    case BIND_STATES::CONNECT_LIFT:
    {
        if (KineticsAccess::getInstance()->CheckActuatorPowerStatus(std::move(LastKineticsResponse)))
        {
            CURRENT_STATE = BIND_STATES::IS_LIFT_ATTACHED;
            Resume();
        }
        else
        {

            CURRENT_STATE = BIND_STATES::IS_LIFT_ATTACHED;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOnMotor(Actuator::LIFT);
        }
        break;
    }

    case BIND_STATES::IS_LIFT_ATTACHED:
    {
        CURRENT_STATE = BIND_STATES::DUMMY_READ_DEGREE_LIFT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorSignalStatus(Actuator::LIFT);
        break;
    }

    case BIND_STATES::DUMMY_READ_DEGREE_LIFT:
    {
        if (KineticsAccess::getInstance()->CheckActuatorSignalStatus(std::move(LastKineticsResponse)))
        {
            KineticsLiftRequest.clear();
            BindedActuatorList.push_back(Actuator::LIFT);
            CURRENT_STATE = BIND_STATES::IS_TILT_CONNECTED;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::READ_DEGREE_LIFT;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::LIFT);
        }
        break;
    }

    case BIND_STATES::READ_DEGREE_LIFT:
    {
        KineticsLiftRequest.push_back(KineticsRequestTiming(100, Actuator::LIFT));
        KineticsLiftRequest.push_back(KineticsRequestDelay(0, Actuator::LIFT));

        CURRENT_STATE = BIND_STATES::SET_DEGREE_LIFT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::LIFT);

        break;
    }

    case BIND_STATES::SET_DEGREE_LIFT:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_LIFT;

        KineticsRequest request = KineticsAccess::getInstance()->GetKineticRequestAngleFromDegreeResponse(Actuator::LIFT, std::move(LastKineticsResponse));
        vector<KineticsRequest> req{
            KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LIFT),
            KineticsRequestEasingInOut(CommandLabels::EasingType::IN, Actuator::LIFT),
            request};

        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);
        break;
    }

    case BIND_STATES::TRIGGER_LIFT:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_LIFT_CONFIRM;

        if (KineticsLiftRequest.size() > 0)
        {
            KineticsLiftRequest.push_back(KineticsRequestTrigger());
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(KineticsLiftRequest);
        }
        else
        {
            Resume();
        }

        break;
    }

    case BIND_STATES::TRIGGER_LIFT_CONFIRM:
    {
        CURRENT_STATE = BIND_STATES::ATTACH_SERVO_LIFT;

        WorkerThread.push_back(std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            try
            {
                /* code */
                vector<KineticsRequest> _TriggerAngles;
                _TriggerAngles.push_back(KineticsRequestTrigger());
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(_TriggerAngles);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }));

        break;
    }

    case BIND_STATES::ATTACH_SERVO_LIFT:
    {
        CURRENT_STATE = BIND_STATES::IS_TILT_CONNECTED;
        if (KineticsLiftRequest.size() > 0)
        {

            if (MachineBindActuators)
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->AttachSignalToActuator(Actuator::LIFT);
                BindedActuatorList.push_back(Actuator::LIFT);
            }
            else
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOffMotor(Actuator::LIFT);
            }
        }
        else
        {
            Resume();
        }
        break;
    }

    case BIND_STATES::IS_TILT_CONNECTED:
    {

        if (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::TILT) != BindedActuatorList.end())
        {

            CURRENT_STATE = BIND_STATES::SET_ACTIVATE_POSITION;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::CONNECT_TILT;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorPowerStatus(Actuator::TILT);
        }

        break;
    }

    case BIND_STATES::CONNECT_TILT:
    {
        if (KineticsAccess::getInstance()->CheckActuatorPowerStatus(std::move(LastKineticsResponse)))
        {
            CURRENT_STATE = BIND_STATES::IS_TILT_ATTACHED;
            Resume();
        }
        else
        {

            CURRENT_STATE = BIND_STATES::IS_TILT_ATTACHED;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOnMotor(Actuator::TILT);
        }
        break;
    }

    case BIND_STATES::IS_TILT_ATTACHED:
    {
        CURRENT_STATE = BIND_STATES::DUMMY_READ_DEGREE_TILT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadActuatorSignalStatus(Actuator::TILT);
        break;
    }

    case BIND_STATES::DUMMY_READ_DEGREE_TILT:
    {
        if (KineticsAccess::getInstance()->CheckActuatorSignalStatus(std::move(LastKineticsResponse)))
        {
            KineticsTiltRequest.clear();
            BindedActuatorList.push_back(Actuator::TILT);
            CURRENT_STATE = BIND_STATES::SET_ACTIVATE_POSITION;
            Resume();
        }
        else
        {
            CURRENT_STATE = BIND_STATES::READ_DEGREE_TILT;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::TILT);
        }
        break;
    }

    case BIND_STATES::READ_DEGREE_TILT:
    {
        KineticsTiltRequest.push_back(KineticsRequestTiming(100, Actuator::TILT));
        KineticsTiltRequest.push_back(KineticsRequestDelay(0, Actuator::TILT));

        CURRENT_STATE = BIND_STATES::SET_DEGREE_TILT;
        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->ReadDegree(Actuator::TILT);

        break;
    }

    case BIND_STATES::SET_DEGREE_TILT:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_TILT;

        KineticsRequest request = KineticsAccess::getInstance()->GetKineticRequestAngleFromDegreeResponse(Actuator::TILT, std::move(LastKineticsResponse));
        vector<KineticsRequest> req{
            KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::TILT),
            KineticsRequestEasingInOut(CommandLabels::EasingType::IN, Actuator::TILT),
            request};

        WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);
        break;
    }

    case BIND_STATES::TRIGGER_TILT:
    {
        CURRENT_STATE = BIND_STATES::TRIGGER_TILT_CONFIRM;

        if (KineticsTiltRequest.size() > 0)
        {
            KineticsTiltRequest.push_back(KineticsRequestTrigger());
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(KineticsTiltRequest);
        }
        else
        {
            Resume();
        }

        break;
    }

    case BIND_STATES::TRIGGER_TILT_CONFIRM:
    {
        CURRENT_STATE = BIND_STATES::ATTACH_SERVO_TILT;

        WorkerThread.push_back(std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            try
            {
                /* code */
                vector<KineticsRequest> _TriggerAngles;
                _TriggerAngles.push_back(KineticsRequestTrigger());
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(_TriggerAngles);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }));
        break;
    }

    case BIND_STATES::ATTACH_SERVO_TILT:
    {
        CURRENT_STATE = BIND_STATES::SET_ACTIVATE_POSITION;
        if (KineticsTiltRequest.size() > 0)
        {

            if (MachineBindActuators)
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->AttachSignalToActuator(Actuator::TILT);
                BindedActuatorList.push_back(Actuator::TILT);
            }
            else
            {
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->PowerOffMotor(Actuator::TILT);
            }
        }
        else
        {
            Resume();
        }
        break;
    }

    case BIND_STATES::SET_ACTIVATE_POSITION:
    {
        if (MachineBindActuators)
        {
            if ((std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::TURN) != BindedActuatorList.end()) &&
                (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::LIFT) != BindedActuatorList.end()) &&
                (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::LEAN) != BindedActuatorList.end()) &&
                (std::find(BindedActuatorList.begin(), BindedActuatorList.end(), Actuator::TILT) != BindedActuatorList.end()))
            {
                CURRENT_STATE = BIND_STATES::MACHINE_BINDED;
                DB_Local_Store dbHAndler;
                Expressions_Type Expression = dbHAndler.readExpression("Play_Straight");
                jsonObject jObject = jsonObject::parse(Expression.Action_Data);
                AnimationPositions Position;
                Position.parseJson(jObject);
                vector<KineticsRequest> requests_stand_straight;

                vector<KineticsRequest> TurnStateCommandSet = (static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Turn).get()))->GetStateCommandString(Actuator::TURN);
                requests_stand_straight.insert(requests_stand_straight.end(), TurnStateCommandSet.begin(), TurnStateCommandSet.end());
                vector<KineticsRequest> LiftStateCommandSet = (static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Lift).get()))->GetStateCommandString(Actuator::LIFT);
                requests_stand_straight.insert(requests_stand_straight.end(), LiftStateCommandSet.begin(), LiftStateCommandSet.end());
                vector<KineticsRequest> LeanStateCommandSet = (static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Lean).get()))->GetStateCommandString(Actuator::LEAN);
                requests_stand_straight.insert(requests_stand_straight.end(), LeanStateCommandSet.begin(), LeanStateCommandSet.end());
                vector<KineticsRequest> TiltStateCommandSet = (static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Tilt).get()))->GetStateCommandString(Actuator::TILT);
                requests_stand_straight.insert(requests_stand_straight.end(), TiltStateCommandSet.begin(), TiltStateCommandSet.end());

                if (TurnStateCommandSet.size() > 0)
                {
                    vector<KineticsRequest> TurnTransitionCommandSet = (static_cast<MotionAnimationTransition*>(Position.Transition.TransitionSet.at(AnimationObject::Motor_Turn).get()))->GetTransitionCommandString(Actuator::TURN);
                    requests_stand_straight.insert(requests_stand_straight.end(), TurnTransitionCommandSet.begin(), TurnTransitionCommandSet.end());
                }
                if (LiftStateCommandSet.size() > 0)
                {
                     vector<KineticsRequest> LiftTransitionCommandSet = (static_cast<MotionAnimationTransition*>(Position.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get()))->GetTransitionCommandString(Actuator::LIFT);
                     requests_stand_straight.insert(requests_stand_straight.end(), LiftTransitionCommandSet.begin(), LiftTransitionCommandSet.end());
                }
                if (LeanStateCommandSet.size() > 0)
                {
                     vector<KineticsRequest> LeanTransitionCommandSet = (static_cast<MotionAnimationTransition*>(Position.Transition.TransitionSet.at(AnimationObject::Motor_Lean).get()))->GetTransitionCommandString(Actuator::LEAN);
                     requests_stand_straight.insert(requests_stand_straight.end(), LeanTransitionCommandSet.begin(), LeanTransitionCommandSet.end());
                }
                if (TiltStateCommandSet.size() > 0)
                {
                     vector<KineticsRequest> TiltTransitionCommandSet = (static_cast<MotionAnimationTransition*>(Position.Transition.TransitionSet.at(AnimationObject::Motor_Tilt).get()))->GetTransitionCommandString(Actuator::TILT);
                     requests_stand_straight.insert(requests_stand_straight.end(), TiltTransitionCommandSet.begin(), TiltTransitionCommandSet.end());
                }
                requests_stand_straight.push_back(KineticsRequestInstantTrigger());
                
                
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(requests_stand_straight);

            }
            else
            {
                CURRENT_STATE = BIND_STATES::IS_TURN_CONNECTED;
                Resume();
            }
        }
        else if (CURRENT_STATE != BIND_STATES::MACHINE_BINDED)
        {
            CURRENT_STATE = BIND_STATES::WAIT_MACHINE_BIND;
        }
        break;
    }

    case BIND_STATES::MACHINE_BINDED:
     printf("binded state");
        notify_BindState(BIND_STATES::MACHINE_BINDED);
        break;

    default:
        printf("default state hit\n");
        break;
    }
}

void MachineBindJOB::notify_BindState(BIND_STATES::STATES State)
{
    printf("in binded call");
    if (BindStateConvey != nullptr)
    {
        printf("binded call");
        BindStateConvey->BindStateChanged(State);
    }
}

MachineBindJOB::~MachineBindJOB()
{

    // for (std::thread &thread : WorkerThread)
    // {
    //     if (thread.joinable())
    //         thread.join();
    // }
}

} // namespace fmSystem