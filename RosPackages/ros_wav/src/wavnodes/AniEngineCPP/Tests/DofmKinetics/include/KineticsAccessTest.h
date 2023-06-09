#pragma once


#include "gtest/gtest.h"
#include "mock_KineticsCommsConvey.h"
#include "mock_KineticsParameterUpdatesConvey.h"
#include "mock_KineticsRemoteRequestConvey.h"
#include "mock_KineticsResponseConvey.h"

#include "FrameworkImplementation/KineticsAccess.h"

class KineticsAccessTest : public ::testing::Test {

protected:

    // // You can do set-up work for each test here.
     KineticsAccessTest();
     void KineticsAccess_SetActuatorParam(Actuator::etype actuator, std::shared_ptr<fmKinetics::KineticsAccess> Instance, long delay);
     std::shared_ptr<mock_KineticsCommsConvey> mock_KineticsCommsConvey_notify{new mock_KineticsCommsConvey()};
     std::shared_ptr<mock_KineticsParameterUpdatesConvey> mock_KineticsParameterUpdatesConvey_notify{new mock_KineticsParameterUpdatesConvey()};
     std::shared_ptr<mock_KineticsRemoteRequestConvey> mock_KineticsRemoteRequestConvey_notify{new mock_KineticsRemoteRequestConvey()};
     std::shared_ptr<mock_KineticsResponseConvey> mock_KineticsResponseConvey_notify{new mock_KineticsResponseConvey()};
};