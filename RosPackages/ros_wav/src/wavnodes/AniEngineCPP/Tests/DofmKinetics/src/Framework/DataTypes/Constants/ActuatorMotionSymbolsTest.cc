#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "Framework/DataTypes/Constants/ActuatorMotionSymbolsTest.h"



ActuatorMotionSymbolsTest::ActuatorMotionSymbolsTest()
{

}

TEST_F(ActuatorMotionSymbolsTest, PortOpenCloseSequence) {
    ActuatorMotionSymbols m_ActuatorMotionSymbols;
    EXPECT_EQ(m_ActuatorMotionSymbols.ConvertFromString("1"), ActuatorMotionSymbols::MOVING);
    EXPECT_EQ(m_ActuatorMotionSymbols.ConvertFromString("0"), ActuatorMotionSymbols::NotMoving);
}

