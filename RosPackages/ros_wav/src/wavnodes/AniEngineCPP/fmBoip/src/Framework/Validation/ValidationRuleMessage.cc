#include "Framework/Validation/ValidationRuleMessage.h"

namespace fmBoip
 {
     ValidationRuleMessage::ValidationRuleMessage(VALIDATION_ERROR_CODES::eType lobjReturn, std::string strAdditionalInfo)
    {
        ErrorCode = lobjReturn;
        AdditionalInfo = strAdditionalInfo;
    }

    ValidationRuleMessage::ValidationRuleMessage(VALIDATION_ERROR_CODES::eType lobjReturn)
    {
        ErrorCode = lobjReturn;
        VALIDATION_ERROR_CODES codes;
        DisplayMessage =  codes.enumtostring.at(ErrorCode);
    }

    ValidationRuleMessage::ValidationRuleMessage(VALIDATION_ERROR_CODES::eType lobjReturn, std::string MethodInfo, std::string strAdditionalInfo)
    {
        ErrorCode = lobjReturn;
        AdditionalInfo = MethodInfo;
        VALIDATION_ERROR_CODES codes;
        DisplayMessage = codes.enumtostring.at(ErrorCode);
    }
 }
