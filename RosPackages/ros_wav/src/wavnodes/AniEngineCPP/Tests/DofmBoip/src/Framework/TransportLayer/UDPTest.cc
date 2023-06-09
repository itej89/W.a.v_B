#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <vector>
#include <string>

#include "Framework/DataTypes/Extras/IPEndPoint.h"
#include "Framework/TransportLayer/UDPTest.h"



UDPTest::UDPTest()
{

}

TEST_F(UDPTest, UDPTest) {
    UDPListen::Instance->StartListening();

    std::string strFrame = "Its BOIP UDP Broadcast test";
    std::vector<uint8_t> Frame(strFrame.begin(), strFrame.end());
    UDPBroadcast::Instance->UDPBroadcastPacket(Frame);
}