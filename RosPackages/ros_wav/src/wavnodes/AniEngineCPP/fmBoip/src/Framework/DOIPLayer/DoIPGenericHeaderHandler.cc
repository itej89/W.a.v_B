#include "Framework/DOIPLayer/DoIPGenericHeaderHandler.h"

namespace fmBoip
{

        std::unique_ptr<DoIPGenericHeaderHandler> DoIPGenericHeaderHandler::Instance(new DoIPGenericHeaderHandler());
        
        bool DoIPGenericHeaderHandler::ValidateHeader(DOIPResponseObject objResponse)
        {
            ValidationErrors.Messages.clear();
            
            std::vector<uint8_t> vecProtocolVersions = DOIPSession::Instance->getValidProtocolVersions();
            
            if(std::find(vecProtocolVersions.begin(), vecProtocolVersions.end(), objResponse.GetProtocolVersion()) != vecProtocolVersions.end())
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Protocol version"));
            }

            if((objResponse.GetInverseProtocolVersion()) != (objResponse.GetProtocolVersion()) ^ 0xFF)
            {
                ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::INVALID_DATA,  "Inverse Protocol version"));
            }
            

            if(ValidationErrors.Messages.size() > 0)
            {
                return false;
            }
            else
            {
                return true;
            }
            
        }
}