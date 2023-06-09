
#include <thread>
#include <chrono>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Activation_Response_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Diagnostic_Message.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Routing_Activation_Requests.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagnosticMessagesDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

#include "VectorX.h"

namespace fmBoip
{
        std::string DiagnosticMessagesDiagState::GetStateID()
        {
            return "DIAGNOSTIC_MESSAGE_DIAG_STATE";
        }

        int DiagnosticMessagesDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
        {
            std::pair<int, std::vector<uint8_t>> retStatus = FormatRequest(arrDataToBeSent);
            if(retStatus.first == DIAGNOSTIC_STATUS::SUCCESS)
            {
                if(retStatus.second.size() > 0)
                {
                    retStatus.first = SendData(retStatus.second);
                }
            }
            return  retStatus.first;
        }

        
        std::pair<int, std::vector<uint8_t>> DiagnosticMessagesDiagState::FormatRequest(std::vector<uint8_t> userData)
        {
            std::vector<uint8_t> data; data;
        
            DOIPFrameSynthesizer formatRequest = DOIPFrameSynthesizer();
            
            std::shared_ptr<Payload_Diagnostic_Message> objDiagnosticMessagePayload(new Payload_Diagnostic_Message());
            
            objDiagnosticMessagePayload->SetSourceAddress(DOIPParameters::Instance->TesterAddress);
            
            if(DOIPSession::Instance->UDSRequestType == ADDRESSING_TYPES::UDS)
            {
                if(DOIPSession::Instance->DaignosticMessageType == ADDRESSING_TYPES::PHYSICAL)
                {
                    objDiagnosticMessagePayload->SetTArgetAddress(DOIPSession::Instance->TargetAddress);
                }
                else
                {
                    if(DOIPSession::Instance->DaignosticMessageType == ADDRESSING_TYPES::FUNCTIONAL)
                    {
                        objDiagnosticMessagePayload->SetTArgetAddress(DOIPParameters::Instance->FunctionaTargetAddress);
                    }
                }
            }
            else
            {
                if(DOIPSession::Instance->UDSRequestType == ADDRESSING_TYPES::TESTER_PRESENT)
                {
                    objDiagnosticMessagePayload->SetTArgetAddress(DOIPParameters::Instance->TesterPresentTargetAddress);
                }
            }
            
            objDiagnosticMessagePayload->SetUserData(userData);
            
            if(objDiagnosticMessagePayload->ValidationErrors.Messages.size() > 0)
            {
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, data);
            }
            
            DOIPRequestObject request = formatRequest.FormHeaderForDoIPFrame(Request_Payload_Types::PLD_DIAG_MESSAGE);
            
            request.SetPayload(objDiagnosticMessagePayload);

            
            data = formatRequest.CreateDOIPFrame(request);
            
            
            return std::make_pair(DIAGNOSTIC_STATUS::SUCCESS, data);
        }

        std::pair<int, std::vector<uint8_t>> DiagnosticMessagesDiagState::HandleIncomingData(DOIPResponseObject objResponse)
        {
            int retStatus = -1;
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {
                std::shared_ptr<PayloadObject> _payloadObject =  objResponse.GetPayload();
                std::shared_ptr<Payload_Diagnostic_Message> Payload =  std::dynamic_pointer_cast<Payload_Diagnostic_Message>(_payloadObject);
             
                if(Payload->Payload.size() > 0)
                {
                    std::vector<uint8_t> userData = Payload->GetUserData();
                    bufferResponse.insert(bufferResponse.begin(), userData.begin(), userData.end());
                  
                    if(Payload->ValidationErrors.Messages.size() > 0)
                    {
                        retStatus = DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                        return std::make_pair(retStatus, bufferResponse);
                    }
                    else
                    {
                        DOIPSession::Instance->LastDiagnosticResponseData.clear();

                            DOIPSession::Instance->LastDiagnosticResponseData.insert(DOIPSession::Instance->LastDiagnosticResponseData.begin(),
                            bufferResponse.begin(), bufferResponse.end());

                        if(DOIPSession::Instance->LastDiagnosticResponseData.size() > 0)
                        {
                            DOIPAccessImplementation::Instance->ContextConvey->UDSResponseRecieved(DOIPSession::Instance->LastDiagnosticResponseData);
                        }
                        return std::make_pair(DIAGNOSTIC_STATUS::COMPLETE, bufferResponse);
                    }
                }
                else
                {
                    ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Diagnostic Message Response Payload"));
                    return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
                }
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Diagnostic Message Response Payload"));
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
            }
        }
    
        int DiagnosticMessagesDiagState::SendData(std::vector<uint8_t> data)
        {
            TcpClient::Instance->_TimeInterval = DOIPParameters::Instance->A_Doip_Diagnostic_Message;
            TcpClient::Instance->Timeout_return_code = DIAGNOSTIC_STATUS::DIAG_ACK_TIMEOUT;
        
            TcpClient::Instance->SendData(data);

            if(TcpClient::Instance->ValidationErrors.Messages.size() > 0)
            {
                return DIAGNOSTIC_STATUS::INTERNAL_ERROR;
            }
            else
            {
                return DIAGNOSTIC_STATUS::SUCCESS;
            }
        }
}