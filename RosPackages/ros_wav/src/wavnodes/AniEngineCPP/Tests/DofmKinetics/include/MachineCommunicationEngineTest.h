#pragma once


#include "gtest/gtest.h"
#include "mock_machine_comms_convey.h"

class MachineCommunicationEngine_Test : public ::testing::Test {

protected:

    // // You can do set-up work for each test here.
     MachineCommunicationEngine_Test();

    
     std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};
};