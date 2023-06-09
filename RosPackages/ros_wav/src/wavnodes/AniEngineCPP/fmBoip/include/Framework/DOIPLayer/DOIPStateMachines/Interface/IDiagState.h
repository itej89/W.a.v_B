#pragma once

#include <stdint-gcc.h>
#include <utility>
#include <string>
	

#include "Framework/Validation/interface/IValidation.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"


namespace fmBoip
{
     class IDiagState  : public IValidation
    {
        public:
          virtual std::string GetStateID() = 0;
          virtual  std::pair<int, std::vector<uint8_t>>  HandleIncomingData(DOIPResponseObject objResponse) = 0;
    };

}