
#include <thread>
#include <chrono>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Activation_Response_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Diagnostic_Message.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Alive_Check_Request.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/DiagnosticMessagesDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"
#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

#include "VectorX.h"

namespace fmBoip
{
        std::string AliveCheckDiagState::GetStateID()
        {
            return "DIAGNOSTIC_MESSAGE_DIAG_STATE";
        }

        int AliveCheckDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
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

        
        std::pair<int, std::vector<uint8_t>> AliveCheckDiagState::FormatRequest(std::vector<uint8_t> userData)
        {
            std::vector<uint8_t> data; data;
        
            DOIPFrameSynthesizer formatRequest = DOIPFrameSynthesizer();
            
            std::shared_ptr<Payload_Alive_Check_Request> objAliveCheckPayload(new Payload_Alive_Check_Request());
            
            objAliveCheckPayload->SetSourceAddress(DOIPParameters::Instance->TesterAddress);
            
            DOIPRequestObject request = formatRequest.FormHeaderForDoIPFrame(Request_Payload_Types::PLD_ALIVE_CHECK_RES);
        
            request.SetPayload(objAliveCheckPayload);
            
            data  = formatRequest.CreateDOIPFrame(request);
            
            return std::make_pair(DIAGNOSTIC_STATUS::SUCCESS, data);
        }

        std::pair<int, std::vector<uint8_t>> AliveCheckDiagState::HandleIncomingData(DOIPResponseObject objResponse)
        {
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {
                 return std::make_pair(_Init(std::vector<uint8_t>()), bufferResponse);
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "AliveCheckDiagState Response Payload"));
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
            }
        }
    
        int AliveCheckDiagState::SendData(std::vector<uint8_t> data)
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