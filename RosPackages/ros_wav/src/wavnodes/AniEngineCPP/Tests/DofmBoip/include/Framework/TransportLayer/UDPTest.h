#pragma once


#include "gtest/gtest.h"
#include "Framework/TransportLayer/UDPListen.h"
#include "Framework/TransportLayer/UDPBroadcast.h"

using namespace fmBoip;

class UDPTest : public ::testing::Test {

protected:

    // // You can do set-up work for each test here.
     UDPTest();
     //std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};
};