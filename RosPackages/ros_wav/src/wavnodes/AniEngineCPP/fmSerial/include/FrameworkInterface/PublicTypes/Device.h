#pragma once

#include <string>

#include <unistd.h>

using std::string;

namespace fmSerial
{
    class Device {
    public:
        string Name = "";
        string UUID = "";
    };
};