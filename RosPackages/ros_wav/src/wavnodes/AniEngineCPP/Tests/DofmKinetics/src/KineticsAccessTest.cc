#include <unistd.h>
#include <limits.h>

#include "memory"
#include <iostream>
#include <fstream>

#include "mock_machine_comms_convey.h"
#include "Framework/MachineCommunicationEngine.h"
#include "MachineCommunicationEngineTest.h"

#include "KineticsAccessTest.h"

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

#include "FrameworkImplementation/KineticsAccess.h"

using ::testing::Return;

using fmKinetics::KineticsAccess;

using fmKinetics::KineticsRequest;
using fmKinetics::KineticsRequestAngle;
using fmKinetics::KineticsRequestAttachLockServo;
using fmKinetics::KineticsRequestAttachServo;
using fmKinetics::KineticsRequestAttentionOff;
using fmKinetics::KineticsRequestAttentionOn;
using fmKinetics::KineticsRequestCELLOne;
using fmKinetics::KineticsRequestCELLThree;
using fmKinetics::KineticsRequestCELLTwo;
using fmKinetics::KineticsRequestConnectPower;
using fmKinetics::KineticsRequestDamp;
using fmKinetics::KineticsRequestDelay;
using fmKinetics::KineticsRequestDettachLockServo;
using fmKinetics::KineticsRequestDettachServo;
using fmKinetics::KineticsRequestDisconnectPower;
using fmKinetics::KineticsRequestEasingInOut;
using fmKinetics::KineticsRequestEEPROMRead;
using fmKinetics::KineticsRequestEEPROMWrite;
using fmKinetics::KineticsRequestForActuator;
using fmKinetics::KineticsRequestFrequency;
using fmKinetics::KineticsRequestInstantTrigger;
using fmKinetics::KineticsRequestISLEEPROMRead;
using fmKinetics::KineticsRequestISLEEPROMWrite;
using fmKinetics::KineticsRequestISLRead;
using fmKinetics::KineticsRequestISLWrite;
using fmKinetics::KineticsRequestLeftLockServoAngle;
using fmKinetics::KineticsRequestLockPowerStatus;
using fmKinetics::KineticsRequestLockSignalStatus;
using fmKinetics::KineticsRequestPowerOff;
using fmKinetics::KineticsRequestPowerOffLockServo;
using fmKinetics::KineticsRequestPowerOnLockServo;
using fmKinetics::KineticsRequestProximityRead;
using fmKinetics::KineticsRequestRightLockServoAngle;
using fmKinetics::KineticsRequestServoDegree;
using fmKinetics::KineticsRequestServoEasing;
using fmKinetics::KineticsRequestServoEEPROMRead;
using fmKinetics::KineticsRequestServoMotionCheck;
using fmKinetics::KineticsRequestServoPowerStatus;
using fmKinetics::KineticsRequestServoSignalStatus;
using fmKinetics::KineticsRequestTiming;
using fmKinetics::KineticsRequestTrigger;
using fmKinetics::KineticsRequestVelocity;

using fmKinetics::KineticsResponse;
using fmKinetics::KineticsResponseAngle;
using fmKinetics::KineticsResponseAttachLockServo;
using fmKinetics::KineticsResponseAttachServo;
using fmKinetics::KineticsResponseAttentionOff;
using fmKinetics::KineticsResponseAttentionOn;
using fmKinetics::KineticsResponseCELLOne;
using fmKinetics::KineticsResponseCELLThree;
using fmKinetics::KineticsResponseCELLTwo;
using fmKinetics::KineticsResponseConnectPower;
using fmKinetics::KineticsResponseDamp;
using fmKinetics::KineticsResponseDelay;
using fmKinetics::KineticsResponseDettachLockServo;
using fmKinetics::KineticsResponseDettachServo;
using fmKinetics::KineticsResponseDisconnectPower;
using fmKinetics::KineticsResponseEasingInOut;
using fmKinetics::KineticsResponseEEPROMRead;
using fmKinetics::KineticsResponseEEPROMWrite;
using fmKinetics::KineticsResponseFrequency;
using fmKinetics::KineticsResponseInstantTrigger;
using fmKinetics::KineticsResponseISLEEPROMRead;
using fmKinetics::KineticsResponseISLEEPROMWrite;
using fmKinetics::KineticsResponseISLRead;
using fmKinetics::KineticsResponseISLWrite;
using fmKinetics::KineticsResponseLeftServoAngle;
using fmKinetics::KineticsResponseLockPowerStatus;
using fmKinetics::KineticsResponseLockSignalStatus;
using fmKinetics::KineticsResponsePowerOff;
using fmKinetics::KineticsResponsePowerOffLockServo;
using fmKinetics::KineticsResponsePowerOnLockServo;
using fmKinetics::KineticsResponseProximityRead;
using fmKinetics::KineticsResponseRightServoAngle;
using fmKinetics::KineticsResponseServoDegree;
using fmKinetics::KineticsResponseServoEasing;
using fmKinetics::KineticsResponseServoEEPROMRead;
using fmKinetics::KineticsResponseServoMotionCheck;
using fmKinetics::KineticsResponseServoPowerStatus;
using fmKinetics::KineticsResponseServoSignalStatus;
using fmKinetics::KineticsResponseTiming;
using fmKinetics::KineticsResponseTrigger;
using fmKinetics::KineticsResponseVelocity;

ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
  std::memcpy(std::get<uIndex>(args), pData, uiDataSize);
}

KineticsAccessTest::KineticsAccessTest()
{
}

void KineticsAccessTest::KineticsAccess_SetActuatorParam(Actuator::etype actuator, std::shared_ptr<KineticsAccess> Instance, long delay)
{
  vector<KineticsRequest> req;

  Instance->ReadActuatorPowerStatus(actuator);
  
  //Instance->CheckActuatorPowerStatus(std::move(mock_KineticsResponseConvey_notify->ResponeData));

  Instance->PowerOnMotor(actuator);
  
  Instance->ReadActuatorSignalStatus(actuator);
 
  //Instance->CheckActuatorSignalStatus(std::move(mock_KineticsResponseConvey_notify->ResponeData));

  Instance->ReadDegree(actuator);
 
  Instance->ReadDegree(actuator);
  



  //KineticsRequestAngle m_KineticsRequestAngle = Instance->GetKineticRequestAngleFromDegreeResponse(actuator, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  KineticsRequestServoEasing m_KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, actuator);
  KineticsRequestEasingInOut m_KineticsRequestEasingInOut(CommandLabels::EasingType::IN, actuator);
  req.clear();
  req.push_back(m_KineticsRequestServoEasing);
  req.push_back(m_KineticsRequestEasingInOut);
  //req.push_back(m_KineticsRequestAngle);
  Instance->SetParameters(req);

  KineticsRequestTiming m_KineticsRequestTiming(100, actuator);
  KineticsRequestDelay m_KineticsRequestDelay(0, actuator);
  KineticsRequestTrigger m_KineticsRequestTrigger;
  req.clear();
  req.push_back(m_KineticsRequestTiming);
  req.push_back(m_KineticsRequestDelay);
  req.push_back(m_KineticsRequestTrigger);
  Instance->SetParameters(req);
 
}

TEST_F(KineticsAccessTest, KineticsAccessTest)
{
  std::shared_ptr<KineticsAccess> Instance = KineticsAccess::getInstance();
  Instance->SetKineticsParameterUpdatesListener(mock_KineticsParameterUpdatesConvey_notify);
  Instance->SetKineticsResposeListener(mock_KineticsResponseConvey_notify);
  Instance->SetCommsDelegate(mock_KineticsCommsConvey_notify);
  Instance->SetMachineRemoteRequestListener(mock_KineticsRemoteRequestConvey_notify);

  long delay = 0000000;

  //Write Actuator addressess to EEPROM
  // Instance->WriteToEEPROM(EEPROMDetails(6, 1), 6);
  // usleep(delay);
  // Instance->WriteToEEPROM(EEPROMDetails(7, 1), 7);
  // usleep(delay);
  // Instance->WriteToEEPROM(EEPROMDetails(8, 1), 8);
  // usleep(delay);
  // Instance->WriteToEEPROM(EEPROMDetails(9, 1), 9);
  // usleep(delay);

  Instance->InitializeComms();

  vector<KineticsRequest> req;
  req.clear();

  
  KineticsRequestTrigger m_KineticsRequestTrigger;
  req.push_back(m_KineticsRequestTrigger);
  Instance->SetParameters(req);
  usleep(delay);

  Instance->StartInstantMotion();
  usleep(delay);

  Instance->ReadActuatorAddress(Actuator::TURN);
  usleep(delay);
  Instance->SetActuatorAddress(Actuator::TURN, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadActuatorAddress(Actuator::LIFT);
  usleep(delay);
  Instance->SetActuatorAddress(Actuator::LIFT, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadActuatorAddress(Actuator::LEAN);
  usleep(delay);
  Instance->SetActuatorAddress(Actuator::LEAN, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadActuatorAddress(Actuator::TILT);
  usleep(delay);
  Instance->SetActuatorAddress(Actuator::TILT, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);

  // std::cout<< std::to_string(MachineConfig::Instance.MachineActuatorList.at(Actuator::TURN)->Address) << std::endl;

  Instance->ReadDeltaResetAngle(Actuator::TURN);
  usleep(delay);
  Instance->SetDeltaResetAngle(Actuator::TURN, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadDeltaResetAngle(Actuator::LIFT);
  usleep(delay);
  Instance->SetDeltaResetAngle(Actuator::LIFT, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadDeltaResetAngle(Actuator::LEAN);
  usleep(delay);
  Instance->SetDeltaResetAngle(Actuator::LEAN, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);
  Instance->ReadDeltaResetAngle(Actuator::TILT);
  usleep(delay);
  Instance->SetDeltaResetAngle(Actuator::TILT, std::move(mock_KineticsResponseConvey_notify->ResponeData));
  usleep(delay);

  Instance->DetachSignalToActuator(Actuator::TURN);
  usleep(delay);
  Instance->DetachSignalToActuator(Actuator::LIFT);
  usleep(delay);
  Instance->DetachSignalToActuator(Actuator::LEAN);
  usleep(delay);
  Instance->DetachSignalToActuator(Actuator::TILT);
  usleep(delay);

   KineticsAccess_SetActuatorParam(Actuator::TURN, Instance, delay);
  KineticsAccess_SetActuatorParam(Actuator::LIFT, Instance, delay);
  KineticsAccess_SetActuatorParam(Actuator::LEAN, Instance, delay);
  KineticsAccess_SetActuatorParam(Actuator::TILT, Instance, delay);

 // Instance->DisconnectMachine();


  while(true)
  {
usleep(3000000);

  }
}