#include <iostream>

#include "Framework/DataTypes/Extras/TransportClientConveyTest.h"


void TransportClientConveyTest::DataRecieved(RecievedData recievedData)
{
    std::cerr << "DataRecieved DataRecieved" << std::endl;
}

void TransportClientConveyTest::Disconnected()
{
    std::cerr << "TransportClientConveyTest Disconnected" << std::endl;
}

void TransportClientConveyTest::Timeout(int code)
{
    std::cerr << "TransportClientConveyTest Timeout" << std::endl;
}