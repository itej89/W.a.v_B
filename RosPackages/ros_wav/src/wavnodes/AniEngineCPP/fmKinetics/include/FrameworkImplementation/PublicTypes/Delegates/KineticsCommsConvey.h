#pragma once

#include <string>

#include "FrameworkImplementation/PublicTypes/Constants/MachineCommsStates.h"
#include "FrameworkImplementation/PublicTypes/Machine.h"

using std::string;

namespace fmKinetics
{
    class  KineticsCommsConvey
    {
        public:
            virtual void commsStateChanged(MachineCommsStates::etype State) = 0;

            virtual void newMachineFound(Machine Device) = 0;
    };
}