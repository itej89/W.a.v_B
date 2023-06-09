#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

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

#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"

#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTest.h"

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

using  fmKinetics::MachineConfig;
using  fmKinetics::CommandLabels::CommandTypes;
using  fmKinetics::CommandLabels::EasingType;
using  fmKinetics::CommandLabels::EasingFunction;

using fmKinetics::EEPROMDetails;


KineticsRequestTest::KineticsRequestTest()
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

TEST_F(KineticsRequestTest, KineticRequestTest) {

    KineticsRequest *m_KineticsRequest = new KineticsRequest(CommandTypes::ANG);
        const char *vinit[] = {"6", "1500"};
        vector<string> items(vinit, std::end(vinit));
    EXPECT_EQ(m_KineticsRequest->formCommand(items), "ANG#6#1500");

    KineticsRequestAngle *m_KineticsRequestAngle = new KineticsRequestAngle(90, fmKinetics::Actuator::TURN);
    EXPECT_EQ(m_KineticsRequestAngle->Request, "~ANG#6#1444:");

    KineticsRequestAttachLockServo *m_KineticsRequestAttachLockServo = new KineticsRequestAttachLockServo(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestAttachLockServo->Request, "~LAT#9:");

    KineticsRequestAttachServo *m_KineticsRequestAttachServo = new KineticsRequestAttachServo(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestAttachServo->Request, "~ATC#9:");

    KineticsRequestAttentionOff *m_KineticsRequestAttentionOff = new KineticsRequestAttentionOff();
    EXPECT_EQ(m_KineticsRequestAttentionOff->Request, "~VNO:");

    KineticsRequestAttentionOn *m_KineticsRequestAttentionOn = new KineticsRequestAttentionOn();
    EXPECT_EQ(m_KineticsRequestAttentionOn->Request, "~VEN:");

    KineticsRequestCELLOne *m_KineticsRequestCELLOne = new KineticsRequestCELLOne();
    EXPECT_EQ(m_KineticsRequestCELLOne->Request, "~CELL1:");

    KineticsRequestCELLThree *m_KineticsRequestCELLThree = new KineticsRequestCELLThree();
    EXPECT_EQ(m_KineticsRequestCELLThree->Request, "~CELL3:");

    KineticsRequestCELLTwo *m_KineticsRequestCELLTwo = new KineticsRequestCELLTwo();
    EXPECT_EQ(m_KineticsRequestCELLTwo->Request, "~CELL2:");

    KineticsRequestConnectPower *m_KineticsRequestConnectPower = new KineticsRequestConnectPower(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestConnectPower->Request, "~CPW#9:");

    KineticsRequestDamp *m_KineticsRequestDamp = new KineticsRequestDamp(5, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestDamp->Request, "~DMP#9#5:");

    KineticsRequestDelay *m_KineticsRequestDelay = new KineticsRequestDelay(50, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestDelay->Request, "~DEL#9#50:");

    KineticsRequestDettachLockServo *m_KineticsRequestDettachLockServo = new KineticsRequestDettachLockServo( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestDettachLockServo->Request, "~LDT#9:");

    KineticsRequestDettachServo *m_KineticsRequestDettachServo = new KineticsRequestDettachServo( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestDettachServo->Request, "~DTC#9:");

    KineticsRequestDisconnectPower *m_KineticsRequestDisconnectPower = new KineticsRequestDisconnectPower( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestDisconnectPower->Request, "~DPW#9:");

    KineticsRequestEasingInOut *m_KineticsRequestEasingInOut = new KineticsRequestEasingInOut(EasingType::OU, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestEasingInOut->Request, "~INO#9#OU:");

    EEPROMDetails *memoryLocation = new EEPROMDetails(0, 1);
    KineticsRequestEEPROMRead *m_KineticsRequestEEPROMRead = new KineticsRequestEEPROMRead(*memoryLocation);
    EXPECT_EQ(m_KineticsRequestEEPROMRead->Request, "~EEPR#0#1:");

    KineticsRequestEEPROMWrite *m_KineticsRequestEEPROMWrite = new KineticsRequestEEPROMWrite(*memoryLocation, 64);
    EXPECT_EQ(m_KineticsRequestEEPROMWrite->Request, "~EEPW#0#1#64:");

    KineticsRequestFrequency *m_KineticsRequestFrequency = new KineticsRequestFrequency(500, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestFrequency->Request, "~FRQ#9#500:");

    KineticsRequestInstantTrigger *m_KineticsRequestInstantTrigger = new KineticsRequestInstantTrigger();
    EXPECT_EQ(m_KineticsRequestInstantTrigger->Request, "~ITRG:");

    KineticsRequestISLEEPROMRead *m_KineticsRequestISLEEPROMRead = new KineticsRequestISLEEPROMRead(1, 0);
    EXPECT_EQ(m_KineticsRequestISLEEPROMRead->Request, "~ISLER#0#1:");

    KineticsRequestISLEEPROMWrite *m_KineticsRequestISLEEPROMWrite = new KineticsRequestISLEEPROMWrite(1,0, 64);
    EXPECT_EQ(m_KineticsRequestISLEEPROMWrite->Request, "~ISLEW#0#1#64:");

    KineticsRequestISLRead *m_KineticsRequestISLRead = new KineticsRequestISLRead(1, 0);
    EXPECT_EQ(m_KineticsRequestISLRead->Request, "~ISLR#0#1:");

    KineticsRequestISLWrite *m_KineticsRequestISLWrite = new KineticsRequestISLWrite(1,0, 64);
    EXPECT_EQ(m_KineticsRequestISLWrite->Request, "~ISLW#0#1#64:");

    KineticsRequestLeftLockServoAngle *m_KineticsRequestLeftLockServoAngle = new KineticsRequestLeftLockServoAngle(90, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestLeftLockServoAngle->Request, "~LLK#9#1444:");

    KineticsRequestLockPowerStatus *m_KineticsRequestLockPowerStatus = new KineticsRequestLockPowerStatus(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestLockPowerStatus->Request, "~LPW#9:");

    KineticsRequestLockSignalStatus *m_KineticsRequestLockSignalStatus = new KineticsRequestLockSignalStatus(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestLockSignalStatus->Request, "~LSA#9:");

    KineticsRequestPowerOff *m_KineticsRequestPowerOff = new KineticsRequestPowerOff();
    EXPECT_EQ(m_KineticsRequestPowerOff->Request, "~POFF:");

    KineticsRequestPowerOffLockServo *m_KineticsRequestPowerOffLockServo = new KineticsRequestPowerOffLockServo(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestPowerOffLockServo->Request, "~LOF#9:");

    KineticsRequestPowerOnLockServo *m_KineticsRequestPowerOnLockServo = new KineticsRequestPowerOnLockServo(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestPowerOnLockServo->Request, "~LON#9:");

    KineticsRequestProximityRead *m_KineticsRequestProximityRead = new KineticsRequestProximityRead(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestProximityRead->Request, "~PRX#9:");

    KineticsRequestRightLockServoAngle *m_KineticsRequestRightLockServoAngle = new KineticsRequestRightLockServoAngle(90, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestRightLockServoAngle->Request, "~RLK#9#1444:");

    KineticsRequestServoDegree *m_KineticsRequestServoDegree = new KineticsRequestServoDegree(fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestServoDegree->Request, "~DEG#9:");

    KineticsRequestServoEasing *m_KineticsRequestServoEasing = new KineticsRequestServoEasing(EasingFunction::SIN, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestServoEasing->Request, "~EAS#9#SIN:");

    KineticsRequestServoEEPROMRead *m_KineticsRequestServoEEPROMRead = new KineticsRequestServoEEPROMRead( fmKinetics::Actuator::TILT, *memoryLocation);
    EXPECT_EQ(m_KineticsRequestServoEEPROMRead->Request, "~SEPR#9#0#1:");

    KineticsRequestServoMotionCheck *m_KineticsRequestServoMotionCheck = new KineticsRequestServoMotionCheck( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestServoMotionCheck->Request, "~SMV#9:");

    KineticsRequestServoPowerStatus *m_KineticsRequestServoPowerStatus = new KineticsRequestServoPowerStatus( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestServoPowerStatus->Request, "~SPW#9:");

    KineticsRequestServoSignalStatus *m_KineticsRequestServoSignalStatus = new KineticsRequestServoSignalStatus( fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestServoSignalStatus->Request, "~SAT#9:");

    KineticsRequestTiming *m_KineticsRequestTiming = new KineticsRequestTiming(1000, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestTiming->Request, "~TMG#9#1000:");

    KineticsRequestTrigger *m_KineticsRequestTrigger = new KineticsRequestTrigger();
    EXPECT_EQ(m_KineticsRequestTrigger->Request, "~TRG:");

    KineticsRequestVelocity *m_KineticsRequestVelocity = new KineticsRequestVelocity(5, fmKinetics::Actuator::TILT);
    EXPECT_EQ(m_KineticsRequestVelocity->Request, "~VEL#9#5:");

}
