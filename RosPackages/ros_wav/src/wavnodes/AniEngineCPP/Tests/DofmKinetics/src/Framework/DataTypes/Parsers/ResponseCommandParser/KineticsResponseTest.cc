#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
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

#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTest.h"

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

using  fmKinetics::MachineConfig;
using  fmKinetics::CommandLabels::CommandTypes;
using  fmKinetics::CommandLabels::EasingType;
using  fmKinetics::CommandLabels::EasingFunction;
using  fmKinetics::ActuatorMotionSymbols;

using fmKinetics::EEPROMDetails;




KineticsResponseTest::KineticsResponseTest()
{
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::TURN)->Address = 6;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::LIFT)->Address = 7;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::LEAN)->Address = 8;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::TILT)->Address = 9;

    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::TURN)->RefPosition = 0;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::LIFT)->RefPosition = 0;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::LEAN)->RefPosition = 0;
    MachineConfig::Instance.MachineActuatorList.at(fmKinetics::Actuator::TILT)->RefPosition = 0;
}

TEST_F(KineticsResponseTest, KineticResponseTest) {


    KineticsResponseAngle *m_KineticsResponseAngle = new KineticsResponseAngle("ANG#6#1444#O:");
    EXPECT_EQ(m_KineticsResponseAngle->ResponseType, fmKinetics::CommandLabels::CommandTypes::ANG);
    EXPECT_EQ(m_KineticsResponseAngle->ActuatorType, fmKinetics::Actuator::TURN);
    EXPECT_EQ(m_KineticsResponseAngle->Angle, 1444);
    EXPECT_EQ(m_KineticsResponseAngle->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseAttachLockServo *m_KineticsResponseAttachLockServo = new KineticsResponseAttachLockServo("LAT#9#O:");
    EXPECT_EQ(m_KineticsResponseAttachLockServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::LAT);
    EXPECT_EQ(m_KineticsResponseAttachLockServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseAttachLockServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseAttachServo *m_KineticsResponseAttachServo = new KineticsResponseAttachServo("ATC#9#O:");
    EXPECT_EQ(m_KineticsResponseAttachServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::ATC);
    EXPECT_EQ(m_KineticsResponseAttachServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseAttachServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseAttentionOff *m_KineticsResponseAttentionOff = new KineticsResponseAttentionOff("VNO#O:");
    EXPECT_EQ(m_KineticsResponseAttentionOff->ResponseType, fmKinetics::CommandLabels::CommandTypes::VNO);
    EXPECT_EQ(m_KineticsResponseAttentionOff->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseAttentionOn *m_KineticsResponseAttentionOn = new KineticsResponseAttentionOn("VEN#O:");
    EXPECT_EQ(m_KineticsResponseAttentionOn->ResponseType, fmKinetics::CommandLabels::CommandTypes::VEN);
    EXPECT_EQ(m_KineticsResponseAttentionOn->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseCELLOne *m_KineticsResponseCELLOne = new KineticsResponseCELLOne("CELL1#O:CELL1#2544:");
    EXPECT_EQ(m_KineticsResponseCELLOne->ResponseType, fmKinetics::CommandLabels::CommandTypes::CELL1);
    EXPECT_EQ(m_KineticsResponseCELLOne->ADC, 2544);
    EXPECT_EQ(m_KineticsResponseCELLOne->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseCELLThree *m_KineticsResponseCELLThree = new KineticsResponseCELLThree("CELL3#O:CELL3#2544:");
    EXPECT_EQ(m_KineticsResponseCELLThree->ResponseType, fmKinetics::CommandLabels::CommandTypes::CELL3);
    EXPECT_EQ(m_KineticsResponseCELLThree->ADC, 2544);
    EXPECT_EQ(m_KineticsResponseCELLThree->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseCELLTwo *m_KineticsResponseCELLTwo = new KineticsResponseCELLTwo("CELL2#O:CELL2#2544:");
    EXPECT_EQ(m_KineticsResponseCELLTwo->ResponseType, fmKinetics::CommandLabels::CommandTypes::CELL2);
    EXPECT_EQ(m_KineticsResponseCELLTwo->ADC, 2544);
    EXPECT_EQ(m_KineticsResponseCELLTwo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseConnectPower *m_KineticsResponseConnectPower = new KineticsResponseConnectPower("~CPW#9#O:");
    EXPECT_EQ(m_KineticsResponseConnectPower->ResponseType, fmKinetics::CommandLabels::CommandTypes::CPW);
    EXPECT_EQ(m_KineticsResponseConnectPower->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseConnectPower->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseDamp *m_KineticsResponseDamp = new KineticsResponseDamp("~DMP#9#5#O:");
    EXPECT_EQ(m_KineticsResponseDamp->ResponseType, fmKinetics::CommandLabels::CommandTypes::DMP);
    EXPECT_EQ(m_KineticsResponseDamp->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseDamp->Damping, 5);
    EXPECT_EQ(m_KineticsResponseDamp->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

    KineticsResponseDelay *m_KineticsResponseDelay = new KineticsResponseDelay("~DEL#9#50#O:");
    EXPECT_EQ(m_KineticsResponseDelay->ResponseType, fmKinetics::CommandLabels::CommandTypes::DEL);
    EXPECT_EQ(m_KineticsResponseDelay->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseDelay->Delay, 50);
    EXPECT_EQ(m_KineticsResponseDelay->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseDettachLockServo *m_KineticsResponseDettachLockServo = new KineticsResponseDettachLockServo( "~LDT#9#O:");
    EXPECT_EQ(m_KineticsResponseDettachLockServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::LDT);
    EXPECT_EQ(m_KineticsResponseDettachLockServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseDettachLockServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseDettachServo *m_KineticsResponseDettachServo = new KineticsResponseDettachServo(  "~DTC#9#O:");
    EXPECT_EQ(m_KineticsResponseDettachServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::DTC);
    EXPECT_EQ(m_KineticsResponseDettachServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseDettachServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseDisconnectPower *m_KineticsResponseDisconnectPower = new KineticsResponseDisconnectPower(  "~DPW#9#O:");
    EXPECT_EQ(m_KineticsResponseDisconnectPower->ResponseType, fmKinetics::CommandLabels::CommandTypes::DPW);
    EXPECT_EQ(m_KineticsResponseDisconnectPower->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseDisconnectPower->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseEasingInOut *m_KineticsResponseEasingInOut = new KineticsResponseEasingInOut("~INO#9#OU#O:");
    EXPECT_EQ(m_KineticsResponseEasingInOut->ResponseType, fmKinetics::CommandLabels::CommandTypes::INO);
    EXPECT_EQ(m_KineticsResponseEasingInOut->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseEasingInOut->EasingType, fmKinetics::CommandLabels::EasingType::OU);
    EXPECT_EQ(m_KineticsResponseEasingInOut->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseEEPROMRead *m_KineticsResponseEEPROMRead = new KineticsResponseEEPROMRead("EEPR#0#O:EEPR#0#1#64:");
    EXPECT_EQ(m_KineticsResponseEEPROMRead->ResponseType, fmKinetics::CommandLabels::CommandTypes::EEPR);
    EXPECT_EQ(m_KineticsResponseEEPROMRead->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseEEPROMRead->Data.at(0), 100);
    EXPECT_EQ(m_KineticsResponseEEPROMRead->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseEEPROMWrite *m_KineticsResponseEEPROMWrite = new KineticsResponseEEPROMWrite("EEPW#0#O:EEPW#0#1#64:");
    EXPECT_EQ(m_KineticsResponseEEPROMWrite->ResponseType, fmKinetics::CommandLabels::CommandTypes::EEPW);
    EXPECT_EQ(m_KineticsResponseEEPROMWrite->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseEEPROMWrite->Data.at(0), 64);
    EXPECT_EQ(m_KineticsResponseEEPROMWrite->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseFrequency *m_KineticsResponseFrequency = new KineticsResponseFrequency("FRQ#9#500#O:");
    EXPECT_EQ(m_KineticsResponseFrequency->ResponseType, fmKinetics::CommandLabels::CommandTypes::FRQ);
    EXPECT_EQ(m_KineticsResponseFrequency->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseFrequency->Frequency, 500);
    EXPECT_EQ(m_KineticsResponseFrequency->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseInstantTrigger *m_KineticsResponseInstantTrigger = new KineticsResponseInstantTrigger("~ITRG#O:");
    EXPECT_EQ(m_KineticsResponseInstantTrigger->ResponseType, fmKinetics::CommandLabels::CommandTypes::ITRG);
    EXPECT_EQ(m_KineticsResponseInstantTrigger->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);



     KineticsResponseISLEEPROMRead *m_KineticsResponseISLEEPROMRead = new KineticsResponseISLEEPROMRead("ISLER#0#O:ISLER#0#1#64:");
    EXPECT_EQ(m_KineticsResponseISLEEPROMRead->ResponseType, fmKinetics::CommandLabels::CommandTypes::ISLER);
    EXPECT_EQ(m_KineticsResponseISLEEPROMRead->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseISLEEPROMRead->Data.at(0), 100);
    EXPECT_EQ(m_KineticsResponseISLEEPROMRead->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseISLEEPROMWrite *m_KineticsResponseISLEEPROMWrite = new KineticsResponseISLEEPROMWrite("ISLEW#0#O:ISLEW#0#1#64:");
    EXPECT_EQ(m_KineticsResponseISLEEPROMWrite->ResponseType, fmKinetics::CommandLabels::CommandTypes::ISLEW);
    EXPECT_EQ(m_KineticsResponseISLEEPROMWrite->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseISLEEPROMWrite->Data.at(0), 64);
    EXPECT_EQ(m_KineticsResponseISLEEPROMWrite->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);



     KineticsResponseISLRead *m_KineticsResponseISLRead = new KineticsResponseISLRead("ISLR#0#O:ISLR#0#1#64:");
    EXPECT_EQ(m_KineticsResponseISLRead->ResponseType, fmKinetics::CommandLabels::CommandTypes::ISLR);
    EXPECT_EQ(m_KineticsResponseISLRead->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseISLRead->Data.at(0), 100);
    EXPECT_EQ(m_KineticsResponseISLRead->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseISLWrite *m_KineticsResponseISLWrite = new KineticsResponseISLWrite("ISLW#0#O:ISLW#0#1#64:");
    EXPECT_EQ(m_KineticsResponseISLWrite->ResponseType, fmKinetics::CommandLabels::CommandTypes::ISLW);
    EXPECT_EQ(m_KineticsResponseISLWrite->Data.size(), 1);
    EXPECT_EQ(m_KineticsResponseISLWrite->Data.at(0), 64);
    EXPECT_EQ(m_KineticsResponseISLWrite->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseLeftServoAngle *m_KineticsResponseLeftServoAngle = new KineticsResponseLeftServoAngle("LLK#9#1444#O:");
    EXPECT_EQ(m_KineticsResponseLeftServoAngle->ResponseType, fmKinetics::CommandLabels::CommandTypes::LLK);
    EXPECT_EQ(m_KineticsResponseLeftServoAngle->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseLeftServoAngle->Angle, 1444);
    EXPECT_EQ(m_KineticsResponseLeftServoAngle->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseLockPowerStatus *m_KineticsResponseLockPowerStatus = new KineticsResponseLockPowerStatus(  "LPW#9#O:LPW#9#1:");
    EXPECT_EQ(m_KineticsResponseLockPowerStatus->ResponseType, fmKinetics::CommandLabels::CommandTypes::LPW);
    EXPECT_EQ(m_KineticsResponseLockPowerStatus->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseLockPowerStatus->PowerState, fmKinetics::ActuatorPowerStatusSymbols::ON);
    EXPECT_EQ(m_KineticsResponseLockPowerStatus->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseLockSignalStatus *m_KineticsResponseLockSignalStatus = new KineticsResponseLockSignalStatus(  "LSA#9#O:LSA#9#1:");
    EXPECT_EQ(m_KineticsResponseLockSignalStatus->ResponseType, fmKinetics::CommandLabels::CommandTypes::LSA);
    EXPECT_EQ(m_KineticsResponseLockSignalStatus->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseLockSignalStatus->SignalState, fmKinetics::ActuatorSignalStatusSymbols::ATTACHED);
    EXPECT_EQ(m_KineticsResponseLockSignalStatus->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponsePowerOff *m_KineticsResponsePowerOff = new KineticsResponsePowerOff("~POFF#O:");
    EXPECT_EQ(m_KineticsResponsePowerOff->ResponseType, fmKinetics::CommandLabels::CommandTypes::POFF);
    EXPECT_EQ(m_KineticsResponsePowerOff->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponsePowerOffLockServo *m_KineticsResponsePowerOffLockServo = new KineticsResponsePowerOffLockServo(  "~LOF#9#O:");
    EXPECT_EQ(m_KineticsResponsePowerOffLockServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::LOF);
    EXPECT_EQ(m_KineticsResponsePowerOffLockServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponsePowerOffLockServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponsePowerOnLockServo *m_KineticsResponsePowerOnLockServo = new KineticsResponsePowerOnLockServo(  "~LON#9#O:");
    EXPECT_EQ(m_KineticsResponsePowerOnLockServo->ResponseType, fmKinetics::CommandLabels::CommandTypes::LON);
    EXPECT_EQ(m_KineticsResponsePowerOnLockServo->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponsePowerOnLockServo->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseProximityRead *m_KineticsResponseProximityRead = new KineticsResponseProximityRead(  "PRX#9#O:PRX#9#1:");
    EXPECT_EQ(m_KineticsResponseProximityRead->ResponseType, fmKinetics::CommandLabels::CommandTypes::PRX);
    EXPECT_EQ(m_KineticsResponseProximityRead->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseProximityRead->MountState, fmKinetics::ProximityStateSymbols::MOUNTED);
    EXPECT_EQ(m_KineticsResponseProximityRead->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseRightServoAngle *m_KineticsResponseRightServoAngle = new KineticsResponseRightServoAngle("~RLK#9#1444#O:");
    EXPECT_EQ(m_KineticsResponseRightServoAngle->ResponseType, fmKinetics::CommandLabels::CommandTypes::RLK);
    EXPECT_EQ(m_KineticsResponseRightServoAngle->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseRightServoAngle->Angle, 1444);
    EXPECT_EQ(m_KineticsResponseRightServoAngle->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseServoDegree *m_KineticsResponseServoDegree = new KineticsResponseServoDegree("DEG#9#O:DEG#9#250:");
    EXPECT_EQ(m_KineticsResponseServoDegree->ResponseType, fmKinetics::CommandLabels::CommandTypes::DEG);
    EXPECT_EQ(m_KineticsResponseServoDegree->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseServoDegree->ADC, 250);
    EXPECT_EQ(m_KineticsResponseServoDegree->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseServoEasing *mKineticsResponseServoEasing = new KineticsResponseServoEasing("~EAS#9#SIN#O:");
    EXPECT_EQ(mKineticsResponseServoEasing->ResponseType, fmKinetics::CommandLabels::CommandTypes::EAS);
    EXPECT_EQ(mKineticsResponseServoEasing->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(mKineticsResponseServoEasing->EasingFunction, EasingFunction::SIN);
    EXPECT_EQ(mKineticsResponseServoEasing->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseServoEEPROMRead *m_KineticsResponseServoEEPROMRead = new KineticsResponseServoEEPROMRead("SEPR#0#1#O:SEPR#9#0#1#64:");
    EXPECT_EQ(m_KineticsResponseServoEEPROMRead->ResponseType, fmKinetics::CommandLabels::CommandTypes::SEPR);
    EXPECT_EQ(m_KineticsResponseServoEEPROMRead->Data.at(0), 100);
    EXPECT_EQ(m_KineticsResponseServoEEPROMRead->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseServoMotionCheck *m_KineticsResponseServoMotionCheck = new KineticsResponseServoMotionCheck("SMV#9#O:SMV#9#1:");
    EXPECT_EQ(m_KineticsResponseServoMotionCheck->ResponseType, fmKinetics::CommandLabels::CommandTypes::SMV);
    EXPECT_EQ(m_KineticsResponseServoMotionCheck->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseServoMotionCheck->ActuatorState, fmKinetics::ActuatorMotionSymbols::MOVING);
    EXPECT_EQ(m_KineticsResponseServoMotionCheck->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseServoPowerStatus *m_KineticsResponseServoPowerStatus = new KineticsResponseServoPowerStatus("SPW#9#O:SPW#9#1:");
    EXPECT_EQ(m_KineticsResponseServoPowerStatus->ResponseType, fmKinetics::CommandLabels::CommandTypes::SPW);
    EXPECT_EQ(m_KineticsResponseServoPowerStatus->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseServoPowerStatus->PowerState, fmKinetics::ActuatorPowerStatusSymbols::ON);
    EXPECT_EQ(m_KineticsResponseServoPowerStatus->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseServoSignalStatus *m_KineticsResponseServoSignalStatus = new KineticsResponseServoSignalStatus("SAT#9#O:SAT#9#1:");
    EXPECT_EQ(m_KineticsResponseServoSignalStatus->ResponseType, fmKinetics::CommandLabels::CommandTypes::SAT);
    EXPECT_EQ(m_KineticsResponseServoSignalStatus->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseServoSignalStatus->SignalState, fmKinetics::ActuatorSignalStatusSymbols::ATTACHED);
    EXPECT_EQ(m_KineticsResponseServoSignalStatus->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseTiming *m_KineticsResponseTiming = new KineticsResponseTiming("~TMG#9#1000#O:");
    EXPECT_EQ(m_KineticsResponseTiming->ResponseType, fmKinetics::CommandLabels::CommandTypes::TMG);
    EXPECT_EQ(m_KineticsResponseTiming->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseTiming->Timing, 1000);
    EXPECT_EQ(m_KineticsResponseTiming->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


     KineticsResponseTrigger *m_KineticsResponseTrigger = new KineticsResponseTrigger("~TRG#O:");
    EXPECT_EQ(m_KineticsResponseTrigger->ResponseType, fmKinetics::CommandLabels::CommandTypes::TRG);
    EXPECT_EQ(m_KineticsResponseTrigger->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);

     KineticsResponseVelocity *m_KineticsResponseVelocity = new KineticsResponseVelocity("~VEL#9#5#O:");
    EXPECT_EQ(m_KineticsResponseVelocity->ResponseType, fmKinetics::CommandLabels::CommandTypes::VEL);
    EXPECT_EQ(m_KineticsResponseVelocity->ActuatorType, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsResponseVelocity->Velocity, 5);
    EXPECT_EQ(m_KineticsResponseVelocity->RequestRecievedAck, fmKinetics::KineticsResponseAcknowledgement::OK);


}