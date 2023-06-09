
#include <thread>
#include <chrono>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/NAK_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Generic_Header_NACK.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/GenericHeaderNAKDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

#include "VectorX.h"

namespace fmBoip
{
        std::string GenericHeaderNAKDiagState::GetStateID()
        {
            return "GENERIC_HEADER_NAK_DIAG_STATE";
        }

        int GenericHeaderNAKDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
        {
            return  true;
        }

        std::pair<int, std::vector<uint8_t>> GenericHeaderNAKDiagState::HandleIncomingData(DOIPResponseObject objResponse)
        {
            
            int retStatus = -1;
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {
                std::shared_ptr<PayloadObject> _payloadObject =  objResponse.GetPayload();
                std::shared_ptr<Payload_Generic_Header_NACK> Payload =  std::dynamic_pointer_cast<Payload_Generic_Header_NACK>(_payloadObject);
             
                if(Payload->Payload.size() > 0)
                {
                    NAK_Codes::CODE code = NAK_Codes::Instance->DECODE(Payload->GetNAK());
                    
                    if(Payload->ValidationErrors.Messages.size() > 0)
                    {
                        retStatus = DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                        return std::make_pair(retStatus, bufferResponse);
                    }

                    DIAGNOSTIC_STATUS _DIAGNOSTIC_STATUS;
                        return std::make_pair(_DIAGNOSTIC_STATUS.HeaderNACKCode_ErrorCode.at(code), bufferResponse);
                    
                }
                else
                {
                    ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Diagnostic Message NAK Payload"));
                    return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
                }
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Diagnostic Message NAK Payload"));
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
            }
        }

        std::pair<int, std::vector<uint8_t>> GenericHeaderNAKDiagState::FormatRequest(std::vector<uint8_t> userData){}
       
        int GenericHeaderNAKDiagState::SendData(std::vector<uint8_t> data){}
}