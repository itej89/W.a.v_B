#pragma once 


#include "Initialization/BindJOB/BIND_STATES.h"


namespace fmSystem
{
    class MachineBindStatusDelegate
    {
        public:
            virtual void BindStateChanged(BIND_STATES::STATES State) = 0;
    };
}