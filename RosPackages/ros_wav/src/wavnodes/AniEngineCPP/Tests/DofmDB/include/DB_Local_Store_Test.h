#pragma once


#include "gtest/gtest.h"
#include "DB_Local_Store.h"

using namespace fmDB;

class DB_Local_Store_Test : public ::testing::Test {

protected:

    // // You can do set-up work for each test here.
     DB_Local_Store_Test();
     //std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};
};