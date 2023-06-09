#pragma once

#include <stdint-gcc.h>
#include <utility>
	

#include "Framework/DOIPLayer/DOIPStateMachines/Interface/IDiagState.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"


namespace fmBoip
{
     class IDiagStateForSendRecieve  : public IDiagState
    {
        public:
           virtual int _Init(std::vector<uint8_t> arrDataToBeSent) = 0;
        
    };

}