#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include <fstream>

#include "Framework/DataTypes/Constants/ProximityStateSymbolsTest.h"



ProximityStateSymbolsTest::ProximityStateSymbolsTest()
{

}

TEST_F(ProximityStateSymbolsTest, PortOpenCloseSequence) {
    ProximityStateSymbols m_ProximityStateSymbols;
    EXPECT_EQ(m_ProximityStateSymbols.ConvertFromString("1"), ProximityStateSymbols::MOUNTED);
    EXPECT_EQ(m_ProximityStateSymbols.ConvertFromString("0"), ProximityStateSymbols::NotMounted);
}

