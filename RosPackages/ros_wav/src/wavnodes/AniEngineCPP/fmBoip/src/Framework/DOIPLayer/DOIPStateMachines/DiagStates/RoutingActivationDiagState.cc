
#include <thread>
#include <chrono>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Activation_Response_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Routing_Activation_Response.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Routing_Activation_Requests.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/RoutingActivationDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

#include "VectorX.h"

namespace fmBoip
{
        std::string RoutingActivationDiagState::GetStateID()
        {
            return "ROUTING_ACTIVATION_DIAG_STATE";
        }

        int RoutingActivationDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
        {
            TcpClient::Instance->TcpClientInit();
            if(TcpClient::Instance->ValidationErrors.Messages.size() == 0)
            {
                bool IsConnectionEstablished = false;
                do{
                    IsConnectionEstablished = TcpClient::Instance->TryConnect(RemoteEndPoint);
                     std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }while (!IsConnectionEstablished);
                
                if(TcpClient::Instance->ValidationErrors.Messages.size() == 0 && IsConnectionEstablished)
                {
                    std::pair<int, std::vector<uint8_t>> retStatus = FormatRequest();
                    data.insert(data.end(), retStatus.second.begin(), retStatus.second.end());
                    if(retStatus.first == DIAGNOSTIC_STATUS::SUCCESS)
                    {
                        if(retStatus.second.size() > 0){
                            retStatus.first = SendData(retStatus.second);
                        }
                    }
                    return  retStatus.first;
                }
                else
                {
                    return DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                }
            }
                
            else
            {
                return DIAGNOSTIC_STATUS::INTERNAL_ERROR;
            }
        }

        
        std::pair<int, std::vector<uint8_t>> RoutingActivationDiagState::FormatRequest()
        {
             std::vector<uint8_t> data; data;

             std::shared_ptr<Payload_Routing_Activation_Requests> objRoutingActivationPAyload(new Payload_Routing_Activation_Requests());
            
            DOIPFrameSynthesizer formatRequest;

            fmCommon::VectorX vecX;

            if(vecX.contains(DOIPSession::Instance->getInvalidAddresses(), DOIPParameters::Instance->TesterAddress))
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Tester Address from configuration"));
                
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, data);
            }
            else
            {
                objRoutingActivationPAyload->SetSourceAddress(DOIPParameters::Instance->TesterAddress);
            }

            objRoutingActivationPAyload->SetActivationType(DOIPParameters::Instance->RoutingActivationType);
            objRoutingActivationPAyload->SetISOReserved(DOIPParameters::Instance->A_DOIP_Activation_Request_ISO_RESERVED);
            
            if(DOIPParameters::Instance->Activation_Request_OEM_BYTES_ENABLED == 1)
            {
                objRoutingActivationPAyload->SetOEMReserved(DOIPParameters::Instance->A_DOIP_Activation_Request_OEM_SPECIFIC);
            }

            DOIPRequestObject request = formatRequest.FormHeaderForDoIPFrame(Request_Payload_Types::PLD_ROUTING_ACTIVATION_REQ);
            
            request.SetPayload(objRoutingActivationPAyload);

            data  = formatRequest.CreateDOIPFrame(request);
            
            return std::make_pair(DIAGNOSTIC_STATUS::SUCCESS, data);
        }

    
        std::pair<int, std::vector<uint8_t>> RoutingActivationDiagState::HandleIncomingData(DOIPResponseObject objResponse) {

            int retStatus = -1;
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {

                 std::shared_ptr<PayloadObject> _payloadObject =  objResponse.GetPayload();
                 Payload_Routing_Activation_Response* Payload = dynamic_cast<Payload_Routing_Activation_Response *>(_payloadObject.get());
                
                if(Payload->Payload.size() > 0)
                {
                    Activation_Response_Codes::CODE  code = Activation_Response_Codes::Instance->DECODE(Payload->GetRoutingActivationResponseCode());
                
                    if(Payload->ValidationErrors.Messages.size() > 0)
                    {
                        retStatus = DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                        delete Payload;
                        return std::make_pair(retStatus, bufferResponse);
                    }
                    
                    if(code == Activation_Response_Codes::RA_RES_CONFIRMATION_REQUIRED)
                    {
                        if(_activationRepeatCount < DOIPParameters::Instance->DOIP_ACTIVATION_CONFIRMATION_REPEAT_COUNT)
                        {
                            if(data.size() > 0)
                            {
                                retStatus = SendData(data);
                                if(retStatus == (DIAGNOSTIC_STATUS::SUCCESS))
                                {
                                    return std::make_pair(retStatus, bufferResponse);
                                }
                                else
                                {
                                    _activationRepeatCount = _activationRepeatCount + 1;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(DOIPParameters::Instance->DOIP_ACTIVATION_CONFIRMATION_REPEAT_TIME));
                                    return std::make_pair(retStatus, bufferResponse); 
                                }
                                
                            }
                            else
                            {
                                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
                            }
                        }
                        else
                        {   _activationRepeatCount = 0;
                            return std::make_pair(DIAGNOSTIC_STATUS::ACTIVATIOMN_CONFIRMATION_TIMEOUT, bufferResponse);
                        }
                    }
                    else if(code != Activation_Response_Codes::RA_RES_SUCCESS)
                    {
                        DIAGNOSTIC_STATUS _DIAGNOSTIC_STATUS;
                        retStatus = _DIAGNOSTIC_STATUS.ResponseCode_ErrorCode.at(code);
                        return std::make_pair(retStatus, bufferResponse);
                    }
                }
                else
                {
                    ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Routing Activation Response Payload"));
                    return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
                }

                if(Payload->GetDOIPEntityLogicalAddress().size() > 0)
                {
                    DOIPSession::Instance->TargetAddress = (Payload->GetDOIPEntityLogicalAddress());
                }

                DOIPAccessImplementation::Instance->StartDOIPSendLoop();
                DOIPAccessImplementation::Instance->ResultConvey->LinkConnected(objResponse.EndPoint);
                return std::make_pair(DIAGNOSTIC_STATUS::COMPLETE, bufferResponse);
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Routing Activation Response Object"));
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
            }

        }

    
        int RoutingActivationDiagState::SendData(std::vector<uint8_t> data)
        {
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