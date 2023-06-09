#pragma once


#include "gtest/gtest.h"
#include "Timer.h"

using namespace fmCommon;

class TimerTest : public ::testing::Test {

public:
void setTimeoutInterval();
void TimeoutInterval();

void setTimeout();
void Timeout();

protected:

    // // You can do set-up work for each test here.
     TimerTest();
     //std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};
};