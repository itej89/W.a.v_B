#pragma once

#include <stdint-gcc.h>
#include <string>
#include <memory>
#include <algorithm>

#include "Framework/Validation/interface/IValidation.h"
#include "Framework/DOIPLayer/DoIPGenericHeaderHandler.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"


#include "Framework/DOIPLayer/DOIPSession.h"



namespace fmBoip
{
     class DoIPGenericHeaderHandler: public IValidation
    {
        public:
        
        static std::unique_ptr<DoIPGenericHeaderHandler> Instance;
        
        bool ValidateHeader(DOIPResponseObject objResponse);
        
    };

}