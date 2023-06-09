#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "FrameworkImplementation/PublicTypes/Constants/MachineRequests.h"
#include "Framework/DataTypes/Parsers/RemoteCommandToMachineRequest.h"
#include "Framework/DataTypes/Parsers/RemoteCommandToMachineRequestTest.h"



RemoteCommandToMachineRequestTest::RemoteCommandToMachineRequestTest()
{

}

TEST_F(RemoteCommandToMachineRequestTest, PortOpenCloseSequence) {
    RemoteCommandToMachineRequest m_RemoteCommandToMachineRequest;
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("PBTN#0#O"), MachineRequests::POWER_BUTTON_PRESSED);
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("PBTN#1#O"), MachineRequests::POWER_BUTTON_DOUBLE_PRESSED);
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("PBTN#2#O"), MachineRequests::POWER_BUTTON_LONG_PRESS);
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("VBTN#0#O"), MachineRequests::ATTENTION_BUTTON_PRESSED);
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("VBTN#1#O"), MachineRequests::ATTENTION_BUTTON_DOUBLE_PRESSED);
    EXPECT_EQ(m_RemoteCommandToMachineRequest.Convert("VBTN#2#O"), MachineRequests::ATTENTION_BUTTON_LONG_PRESS);
}