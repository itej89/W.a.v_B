#pragma once

#include <string>

#include "../Constants/MachineCommsStates.h"
#include "../Machine.h"
#include "../Constants/MachineRequests.h"

using std::string;

namespace fmKinetics
{
    class  KineticsRemoteRequestConvey
    {
        public:
            virtual void machineRequested(MachineRequests::etype Request) = 0;
    };
}