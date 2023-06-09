#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
#include <memory>

#include "Framework/TransportLayer/TCPTest.h"
#include "Framework/DataTypes/Extras/TransportClientConveyTest.h"




TCPTest::TCPTest()
{

}

TEST_F(TCPTest, TCPTest) {

    TcpClient::Instance->TcpClientInit();
    TcpClient::Instance->ClientConvey.reset(new TransportClientConveyTest());
    TcpClient::Instance->TryConnect();

    std::string strFrame = "Its BOIP TCP Broadcast test";
    std::vector<uint8_t> Frame(strFrame.begin(), strFrame.end());
    TcpClient::Instance->SendData(Frame);

}