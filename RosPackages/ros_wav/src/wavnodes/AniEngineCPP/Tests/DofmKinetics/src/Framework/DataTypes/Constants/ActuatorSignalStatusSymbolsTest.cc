#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "Framework/DataTypes/Constants/ActuatorSignalStatusSymbolsTest.h"



ActuatorSignalStatusSymbolsTest::ActuatorSignalStatusSymbolsTest()
{

}

TEST_F(ActuatorSignalStatusSymbolsTest, PortOpenCloseSequence) {
    ActuatorSignalStatusSymbols m_ActuatorSignalStatusSymbols;
    EXPECT_EQ(m_ActuatorSignalStatusSymbols.ConvertFromString("1"), ActuatorSignalStatusSymbols::ATTACHED);
    EXPECT_EQ(m_ActuatorSignalStatusSymbols.ConvertFromString("0"), ActuatorSignalStatusSymbols::DETTACHED);
}

