#pragma once

#include <string>

#include "Framework/Validation/VALIDATION_ERROR_CODES.h"

namespace fmBoip
 {

    class ValidationRuleMessage {
        public:
        ValidationRuleMessage(VALIDATION_ERROR_CODES::eType lobjReturn, std::string strAdditionalInfo);

        ValidationRuleMessage(VALIDATION_ERROR_CODES::eType  lobjReturn);

        ValidationRuleMessage(VALIDATION_ERROR_CODES::eType  lobjReturn, std::string MethodInfo, std::string strAdditionalInfo);
        
        private:
        std::string AdditionalInfo;
        VALIDATION_ERROR_CODES::eType ErrorCode;
        std::string DisplayMessage;
    };

}
