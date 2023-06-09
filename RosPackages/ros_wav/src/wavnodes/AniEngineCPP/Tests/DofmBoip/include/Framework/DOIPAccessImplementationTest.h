#pragma once


#include <memory>

#include "gtest/gtest.h"

#include "Framework/DOIPAccessImplementation.h"
#include "Framework/DataTypes/Extras/DOIPContextResultConveyTest.h"
#include "Framework/DataTypes/Extras/DOIPContextConveyTest.h"

using namespace fmBoip;

class DOIPAccessImplementationTest : public ::testing::Test {
    protected:
        // // You can do set-up work for each test here.
        DOIPAccessImplementationTest();
        //std::shared_ptr<mock_machine_comms_convey> mock_machine_comms_notify{new mock_machine_comms_convey()};

    public:
        
        std::shared_ptr<DOIPContextConveyTest>  _DOIPContextConveyTest;
        std::shared_ptr<DOIPContextResultConveyTest>  _DOIPContextResultConveyTest;
};