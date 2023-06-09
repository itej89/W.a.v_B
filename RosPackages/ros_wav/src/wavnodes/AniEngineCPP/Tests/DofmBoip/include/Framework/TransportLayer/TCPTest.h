#pragma once


#include "gtest/gtest.h"

#include "Framework/TransportLayer/TcpClient.h"


using namespace fmBoip;

class TCPTest : public ::testing::Test {

protected:


    // // You can do set-up work for each test here.
     TCPTest();
     //std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};
};