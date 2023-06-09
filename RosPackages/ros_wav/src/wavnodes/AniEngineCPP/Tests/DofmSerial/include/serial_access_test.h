#pragma once


#include "gtest/gtest.h"
#include "mock_comms_convey.h"
#include "mock_serial.h"
#include "serial_access.h"

using namespace fmSerial;

class serial_access_test : public ::testing::Test {

protected:

    // // You can do set-up work for each test here.
     serial_access_test();

    // // You can do clean-up work that doesn't throw exceptions here.
    // virtual ~serial_access_test();

    // // If the constructor and destructor are not enough for setting up
    // // and cleaning up each test, you can define the following methods:

    // // Code here will be called immediately after the constructor (right
    // // before each test).
    // virtual void SetUp();

    // // Code here will be called immediately after each test (right
    // // before the destructor).
    // virtual void TearDown();
    
     std::shared_ptr<mock_serial> m_serial{new mock_serial()};
     std::shared_ptr<mock_comms_convey> m_serial_access_notify{new mock_comms_convey()};
};