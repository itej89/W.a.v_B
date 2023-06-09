
#include <thread>
#include <chrono>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_ACK_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Diagnostic_Message_Ack.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagMessagePosACKDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

#include "VectorX.h"

namespace fmBoip
{
        std::string DiagMessagePosACKDiagState::GetStateID()
        {
            return "DIAGNOSTIC_MESSAGE_POS_ACK_DIAG_STATE";
        }

        int DiagMessagePosACKDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
        {
            return  true;
        }

        std::pair<int, std::vector<uint8_t>> DiagMessagePosACKDiagState::HandleIncomingData(DOIPResponseObject objResponse)
        {
            
            int retStatus = -1;
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {
                std::shared_ptr<PayloadObject> _payloadObject =  objResponse.GetPayload();
                std::shared_ptr<Payload_Diagnostic_Message_Ack> Payload =  std::dynamic_pointer_cast<Payload_Diagnostic_Message_Ack>(_payloadObject);
             
                if(Payload->Payload.size() > 0 && Diagnostic_ACK_Codes::Instance->VALUE_TO_CODE.find(Payload->GetAcknowledgement()) != Diagnostic_ACK_Codes::Instance->VALUE_TO_CODE.end())
                {
                    Diagnostic_ACK_Codes::CODE ack = Diagnostic_ACK_Codes::Instance->VALUE_TO_CODE.at(Payload->GetAcknowledgement());
                    
                    if(Payload->ValidationErrors.Messages.size() > 0)
                    {
                        retStatus = DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                        return std::make_pair(retStatus, bufferResponse);
                    }
                      else
                if(Diagnostic_ACK_Codes::Instance->DECODE(ack) == Diagnostic_ACK_Codes::DIAG_ACK_PASS)
                {
                    retStatus = DIAGNOSTIC_STATUS::SUCCESS;
                    return std::make_pair(retStatus, bufferResponse);
                }
                else
                    {
                        retStatus = DIAGNOSTIC_STATUS::RESERVED_ISO13400;
                        return std::make_pair(retStatus, bufferResponse);
                    }
                    
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

        std::pair<int, std::vector<uint8_t>> DiagMessagePosACKDiagState::FormatRequest(std::vector<uint8_t> userData){}
       
        int DiagMessagePosACKDiagState::SendData(std::vector<uint8_t> data){}
}