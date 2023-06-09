#pragma once

#include <string>
#include <list> 

#include "Framework/Validation/ValidationRuleMessage.h"


namespace fmBoip
 {

    class ValidationRuleMessages {
        public:
        void add(ValidationRuleMessage _validationRuleMessage);

        std::list<ValidationRuleMessage> Messages;
    };

}