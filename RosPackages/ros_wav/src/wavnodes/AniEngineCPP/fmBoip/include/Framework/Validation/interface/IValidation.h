#pragma once

#include <string>

#include "Framework/Validation/ValidationRuleMessages.h"


namespace fmBoip
{
    class IValidation
    {
        public:
         ValidationRuleMessages ValidationErrors;
    };
}