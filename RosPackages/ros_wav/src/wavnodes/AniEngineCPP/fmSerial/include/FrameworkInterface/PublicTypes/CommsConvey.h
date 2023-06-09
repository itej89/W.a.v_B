#pragma once

#include <string>

#include "Constants/CommsStates.h"
#include "Device.h"


using std::string;

namespace fmSerial
{

class CommsConvey
{

public:

    virtual void serialStataChanged (CommsStates State) = 0;
    virtual void newDeviceDiscovered (string DeviceID) = 0;
    virtual void stringRecieved (string d) = 0;
};

};

