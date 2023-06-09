#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "mock_machine_comms_convey.h"
#include "Framework/MachineCommunicationEngine.h"
#include "MachineCommunicationEngineTest.h"



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


using ::testing::Return;

using fmKinetics::MachineCommunicationEngine;

using  fmKinetics::KineticsRequest;
using  fmKinetics::KineticsRequestAngle;
using  fmKinetics::KineticsRequestAttachLockServo;
using  fmKinetics::KineticsRequestAttachServo;
using  fmKinetics::KineticsRequestAttentionOff;
using  fmKinetics::KineticsRequestAttentionOn;
using  fmKinetics::KineticsRequestCELLOne;
using  fmKinetics::KineticsRequestCELLThree;
using  fmKinetics::KineticsRequestCELLTwo;
using  fmKinetics::KineticsRequestConnectPower;
using  fmKinetics::KineticsRequestDamp;
using  fmKinetics::KineticsRequestDelay;
using  fmKinetics::KineticsRequestDettachLockServo;
using  fmKinetics::KineticsRequestDettachServo;
using  fmKinetics::KineticsRequestDisconnectPower;
using  fmKinetics::KineticsRequestEasingInOut;
using  fmKinetics::KineticsRequestEEPROMRead;
using  fmKinetics::KineticsRequestEEPROMWrite;
using  fmKinetics::KineticsRequestForActuator;
using  fmKinetics::KineticsRequestFrequency;
using  fmKinetics::KineticsRequestInstantTrigger;
using  fmKinetics::KineticsRequestISLEEPROMRead;
using  fmKinetics::KineticsRequestISLEEPROMWrite;
using  fmKinetics::KineticsRequestISLRead;
using  fmKinetics::KineticsRequestISLWrite;
using  fmKinetics::KineticsRequestLeftLockServoAngle;
using  fmKinetics::KineticsRequestLockPowerStatus;
using  fmKinetics::KineticsRequestLockSignalStatus;
using  fmKinetics::KineticsRequestPowerOff;
using  fmKinetics::KineticsRequestPowerOffLockServo;
using  fmKinetics::KineticsRequestPowerOnLockServo;
using  fmKinetics::KineticsRequestProximityRead;
using  fmKinetics::KineticsRequestRightLockServoAngle;
using  fmKinetics::KineticsRequestServoDegree;
using  fmKinetics::KineticsRequestServoEasing;
using  fmKinetics::KineticsRequestServoEEPROMRead;
using  fmKinetics::KineticsRequestServoMotionCheck;
using  fmKinetics::KineticsRequestServoPowerStatus;
using  fmKinetics::KineticsRequestServoSignalStatus;
using  fmKinetics::KineticsRequestTiming;
using  fmKinetics::KineticsRequestTrigger;
using  fmKinetics::KineticsRequestVelocity;

using  fmKinetics::KineticsResponse;
using  fmKinetics::KineticsResponseAngle;
using  fmKinetics::KineticsResponseAttachLockServo;
using  fmKinetics::KineticsResponseAttachServo;
using  fmKinetics::KineticsResponseAttentionOff;
using  fmKinetics::KineticsResponseAttentionOn;
using  fmKinetics::KineticsResponseCELLOne;
using  fmKinetics::KineticsResponseCELLThree;
using  fmKinetics::KineticsResponseCELLTwo;
using  fmKinetics::KineticsResponseConnectPower;
using  fmKinetics::KineticsResponseDamp;
using  fmKinetics::KineticsResponseDelay;
using  fmKinetics::KineticsResponseDettachLockServo;
using  fmKinetics::KineticsResponseDettachServo;
using  fmKinetics::KineticsResponseDisconnectPower;
using  fmKinetics::KineticsResponseEasingInOut;
using  fmKinetics::KineticsResponseEEPROMRead;
using  fmKinetics::KineticsResponseEEPROMWrite;
using  fmKinetics::KineticsResponseFrequency;
using  fmKinetics::KineticsResponseInstantTrigger;
using  fmKinetics::KineticsResponseISLEEPROMRead;
using  fmKinetics::KineticsResponseISLEEPROMWrite;
using  fmKinetics::KineticsResponseISLRead;
using  fmKinetics::KineticsResponseISLWrite;
using  fmKinetics::KineticsResponseLeftServoAngle;
using  fmKinetics::KineticsResponseLockPowerStatus;
using  fmKinetics::KineticsResponseLockSignalStatus;
using  fmKinetics::KineticsResponsePowerOff;
using  fmKinetics::KineticsResponsePowerOffLockServo;
using  fmKinetics::KineticsResponsePowerOnLockServo;
using  fmKinetics::KineticsResponseProximityRead;
using  fmKinetics::KineticsResponseRightServoAngle;
using  fmKinetics::KineticsResponseServoDegree;
using  fmKinetics::KineticsResponseServoEasing;
using  fmKinetics::KineticsResponseServoEEPROMRead;
using  fmKinetics::KineticsResponseServoMotionCheck;
using  fmKinetics::KineticsResponseServoPowerStatus;
using  fmKinetics::KineticsResponseServoSignalStatus;
using  fmKinetics::KineticsResponseTiming;
using  fmKinetics::KineticsResponseTrigger;
using  fmKinetics::KineticsResponseVelocity;

ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
    std::memcpy(std::get<uIndex>(args), pData, uiDataSize);
}


    uint8_t rcvBuffer[] = "TMG#6#1000#O:";
    size_t bufferSize = sizeof("TMG#6#1000#O:");

MachineCommunicationEngine_Test::MachineCommunicationEngine_Test()
{
    // ON_CALL(*m_serial,isOpen()).WillByDefault(Return(true));

    // EXPECT_CALL( *m_serial, readToBuffer( testing::_, testing::_) )
    // .WillRepeatedly( testing::DoAll(
    //     SetArgNPointeeTo<0>(std::begin(rcvBuffer), bufferSize),
    //     testing::Return( 13  ) ) );
}

TEST_F(MachineCommunicationEngine_Test, MachineCommunicationEngineTest) {

    std::shared_ptr<MachineCommunicationEngine> machineCommunicationEngine{new MachineCommunicationEngine()};
    machineCommunicationEngine->SetCommsDelegate(mock_machine_comms_notify);
    machineCommunicationEngine->InitializeComms();
    EXPECT_EQ(machineCommunicationEngine->IsConnectedToMachine(), true);


     KineticsRequestTrigger m_KineticsRequestTrigger;
     KineticsRequestInstantTrigger m_KineticsRequestInstantTrigger;
     KineticsRequestAngle *m_KineticsRequestAngle = new KineticsRequestAngle(90, Actuator::etype::TURN);
     KineticsRequestAttachServo *m_KineticsRequestAttachServo = new KineticsRequestAttachServo(Actuator::etype::TURN);
     KineticsRequestAttentionOff m_KineticsRequestAttentionOff;
     KineticsRequestAttentionOn m_KineticsRequestAttentionOn;
     KineticsRequestCELLOne m_KineticsRequestCELLOne;
     KineticsRequestCELLThree m_KineticsRequestCELLThree;
     KineticsRequestCELLTwo m_KineticsRequestCELLTwo;
     KineticsRequestConnectPower *m_KineticsRequestConnectPower = new KineticsRequestConnectPower(Actuator::etype::TURN);
     KineticsRequestDamp *m_KineticsRequestDamp = new KineticsRequestDamp(2, Actuator::etype::TURN);
     KineticsRequestDelay *m_KineticsRequestDelay = new KineticsRequestDelay(500, Actuator::etype::TURN);
     KineticsRequestDettachServo *m_KineticsRequestDettachServo = new KineticsRequestDettachServo(Actuator::etype::TURN);
     KineticsRequestDisconnectPower *m_KineticsRequestDisconnectPower = new KineticsRequestDisconnectPower(Actuator::etype::TURN);
     KineticsRequestEasingInOut *m_KineticsRequestEasingInOut = new KineticsRequestEasingInOut(fmKinetics::CommandLabels::EasingType::IN, Actuator::etype::TURN);
    
     fmKinetics::EEPROMDetails *memoryLocation = new fmKinetics::EEPROMDetails(0, 1);
     KineticsRequestEEPROMRead *m_KineticsRequestEEPROMRead = new KineticsRequestEEPROMRead(*memoryLocation);
     KineticsRequestEEPROMWrite *m_KineticsRequestEEPROMWrite = new KineticsRequestEEPROMWrite(*memoryLocation, 64);
     KineticsRequestFrequency *m_KineticsRequestFrequency = new KineticsRequestFrequency(500, fmKinetics::Actuator::TILT);
      KineticsRequestISLEEPROMRead *m_KineticsRequestISLEEPROMRead = new KineticsRequestISLEEPROMRead(1, 0);
      KineticsRequestISLEEPROMWrite *m_KineticsRequestISLEEPROMWrite = new KineticsRequestISLEEPROMWrite(1,0, 64);
      KineticsRequestISLRead *m_KineticsRequestISLRead = new KineticsRequestISLRead(1, 0);
      KineticsRequestISLWrite *m_KineticsRequestISLWrite = new KineticsRequestISLWrite(1,0, 64);
      KineticsRequestLeftLockServoAngle *m_KineticsRequestLeftLockServoAngle = new KineticsRequestLeftLockServoAngle(90, fmKinetics::Actuator::TILT);
      KineticsRequestLockPowerStatus *m_KineticsRequestLockPowerStatus = new KineticsRequestLockPowerStatus(fmKinetics::Actuator::TILT);
      KineticsRequestLockSignalStatus *m_KineticsRequestLockSignalStatus = new KineticsRequestLockSignalStatus(fmKinetics::Actuator::TILT);
      KineticsRequestPowerOff *m_KineticsRequestPowerOff = new KineticsRequestPowerOff();
      KineticsRequestPowerOffLockServo *m_KineticsRequestPowerOffLockServo = new KineticsRequestPowerOffLockServo(fmKinetics::Actuator::TILT);
      KineticsRequestPowerOnLockServo *m_KineticsRequestPowerOnLockServo = new KineticsRequestPowerOnLockServo(fmKinetics::Actuator::TILT);
      KineticsRequestProximityRead *m_KineticsRequestProximityRead = new KineticsRequestProximityRead(fmKinetics::Actuator::TILT);
      KineticsRequestServoDegree *m_KineticsRequestServoDegree = new KineticsRequestServoDegree(fmKinetics::Actuator::TILT);
      KineticsRequestServoEasing *m_KineticsRequestServoEasing = new KineticsRequestServoEasing(fmKinetics::CommandLabels::EasingFunction::SIN, fmKinetics::Actuator::TILT);
      KineticsRequestServoEEPROMRead *m_KineticsRequestServoEEPROMRead = new KineticsRequestServoEEPROMRead( fmKinetics::Actuator::TILT, *memoryLocation);
      KineticsRequestServoMotionCheck *m_KineticsRequestServoMotionCheck = new KineticsRequestServoMotionCheck( fmKinetics::Actuator::TILT);
      KineticsRequestServoPowerStatus *m_KineticsRequestServoPowerStatus = new KineticsRequestServoPowerStatus( fmKinetics::Actuator::TILT);
      KineticsRequestServoSignalStatus *m_KineticsRequestServoSignalStatus = new KineticsRequestServoSignalStatus( fmKinetics::Actuator::TILT);
      KineticsRequestTiming *m_KineticsRequestTiming = new KineticsRequestTiming(1000, fmKinetics::Actuator::TILT);
      KineticsRequestVelocity *m_KineticsRequestVelocity = new KineticsRequestVelocity(5, fmKinetics::Actuator::TILT);


     
     vector<KineticsRequest> requestVector {m_KineticsRequestTrigger, 
                                            m_KineticsRequestInstantTrigger,
                                           *m_KineticsRequestAngle,
                                           *m_KineticsRequestAttachServo,
                                           m_KineticsRequestAttentionOff,
                                           m_KineticsRequestAttentionOn,
                                           m_KineticsRequestCELLOne,
                                           m_KineticsRequestCELLThree,
                                           m_KineticsRequestCELLTwo,
                                           *m_KineticsRequestConnectPower,
                                           *m_KineticsRequestDamp,
                                           *m_KineticsRequestDelay,
                                           *m_KineticsRequestDettachServo,
                                           *m_KineticsRequestDisconnectPower,
                                           *m_KineticsRequestEasingInOut,
                                           *m_KineticsRequestEEPROMRead,
                                           *m_KineticsRequestEEPROMWrite,
                                           *m_KineticsRequestFrequency,
                                           *m_KineticsRequestISLEEPROMRead,
                                           *m_KineticsRequestISLEEPROMWrite,
                                           *m_KineticsRequestISLRead,
                                           *m_KineticsRequestISLWrite,
                                           *m_KineticsRequestProximityRead,
                                           *m_KineticsRequestServoDegree,
                                           *m_KineticsRequestServoEasing,
                                           *m_KineticsRequestServoMotionCheck,
                                           *m_KineticsRequestServoPowerStatus,
                                           *m_KineticsRequestServoSignalStatus,
                                           *m_KineticsRequestTiming,
                                           *m_KineticsRequestVelocity
                                        };


    //  KineticsResponseTrigger *m_KineticsResponseTrigger = new KineticsResponseTrigger("~TRG#O:");
    //  vector<KineticsResponse> responseVector {*m_KineticsResponseTrigger};

     //UUID retUID = machineCommunicationEngine->SendData(requestVector);
    // EXPECT_CALL(*mock_machine_comms_notify, RecievedResponseData(responseVector, retUID)); // << "i is : " << i << std::endl;
     //usleep(1000000);

     
    // char exec_path_buff[PATH_MAX];
    // ssize_t len = ::readlink("/proc/self/exe", exec_path_buff, sizeof(exec_path_buff)-1);
    // string exec_path(exec_path_buff); 
    // std::ifstream Command_file(exec_path.substr(0,exec_path.find_last_of("//"))+"/CommandList.txt");
     

    // if(Command_file.good()) 
    //     std::cout << "true" << std::endl;

    // json j;
    // Command_file >> j; 


    //  for (int i=0; i<2; i++)
    //  {
    //      string Tx = j["Commands"][i]["Tx"].get<string>();
    //     EXPECT_EQ(serial_access.SendString(Tx), Tx.size());
    //     string Rx = j["Commands"][i]["Rx"].get<string>();
    //     EXPECT_CALL(*m_serial_access_notify, stringRecieved(Rx)); // << "i is : " << i << std::endl;
    //     usleep(100000);
       
    //  }

    machineCommunicationEngine->DisconnectMachine();
}