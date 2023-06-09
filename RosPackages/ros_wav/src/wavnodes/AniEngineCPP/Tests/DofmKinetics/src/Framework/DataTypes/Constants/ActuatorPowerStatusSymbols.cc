#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "Framework/DataTypes/Constants/ActuatorPowerStatusSymbolsTest.h"



ActuatorPowerStatusSymbolsTest::ActuatorPowerStatusSymbolsTest()
{

}

TEST_F(ActuatorPowerStatusSymbolsTest, PortOpenCloseSequence) {
    ActuatorPowerStatusSymbols m_ActuatorPowerStatusSymbols;
    EXPECT_EQ(m_ActuatorPowerStatusSymbols.ConvertFromString("1"), ActuatorPowerStatusSymbols::ON);
    EXPECT_EQ(m_ActuatorPowerStatusSymbols.ConvertFromString("0"), ActuatorPowerStatusSymbols::OFF);
}

