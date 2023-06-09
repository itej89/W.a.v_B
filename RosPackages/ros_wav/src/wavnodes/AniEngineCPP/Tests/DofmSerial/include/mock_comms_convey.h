
#pragma once

#include "gmock/gmock.h"

#include "FrameworkInterface/PublicTypes/CommsConvey.h"
#include "FrameworkInterface/PublicTypes/Constants/CommsStates.h"

using fmSerial::CommsConvey;
using fmSerial::CommsStates;

class mock_comms_convey: public CommsConvey
{
    public:

    MOCK_METHOD(void, serialStataChanged, (CommsStates State), (override));
    MOCK_METHOD(void, newDeviceDiscovered, (string DeviceID), (override));
    MOCK_METHOD(void, stringRecieved, (string d), (override));
}; 