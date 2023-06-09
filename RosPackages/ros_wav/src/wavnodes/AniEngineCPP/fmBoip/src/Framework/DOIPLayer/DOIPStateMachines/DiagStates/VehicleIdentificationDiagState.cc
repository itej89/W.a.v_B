#include <iostream>

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"
#include "Framework/TransportLayer/UDPBroadcast.h"
#include "Framework/DOIPLayer/DOIPSession.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Vehicle_Announcement.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DiagStates/VehicleIdentificationDiagState.h"
#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"
#include "Framework/DOIPAccessImplementation.h"

namespace fmBoip
{

    std::string VehicleIdentificationDiagState::GetStateID()
    {
        return "VEHICLE_IDENTIFICATION_DIAG_STATE";
    }

  int VehicleIdentificationDiagState::_Init(std::vector<uint8_t> arrDataToBeSent)  
         {
            if(UDPListen::Instance->ValidationErrors.Messages.size() == 0)
            {
                std::vector<uint8_t> data;
                std::pair<int, std::vector<uint8_t>>  returnStatus = FormatRequest();
                if(returnStatus.first == DIAGNOSTIC_STATUS::SUCCESS)
                {
                    data = returnStatus.second;
                    if(data.size() != 0)
                    {
                        DOIPSession::Instance->RespondedDOIPEntityCachedData = DOIPEntity();
                        returnStatus.first = SendData(data);
                    }
                    return returnStatus.first;
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

        
        std::pair<int, std::vector<uint8_t>> VehicleIdentificationDiagState::FormatRequest()
        {
             std::vector<uint8_t> data; data;
            
            DOIPFrameSynthesizer formatRequest;
            
            DOIPRequestObject request = formatRequest.FormHeaderForDoIPFrame(Request_Payload_Types::PLD_VEH_IDEN_REQ);
            
            data  = formatRequest.CreateDOIPFrame(request);
            
            return std::make_pair(DIAGNOSTIC_STATUS::SUCCESS, data);
        }

    
        std::pair<int, std::vector<uint8_t>> VehicleIdentificationDiagState::HandleIncomingData(DOIPResponseObject objResponse) {

            int retStatus = -1;
            std::vector<uint8_t> bufferResponse;
            
            if(objResponse.GetProtocolVersion() != objResponse.GetInverseProtocolVersion())
            {
                DOIPSession::Instance->ProtocolVersion = objResponse.GetProtocolVersion();
                
                 std::shared_ptr<PayloadObject> _payloadObject =  objResponse.GetPayload();
                // Payload_Vehicle_Announcement* Payload = dynamic_cast<Payload_Vehicle_Announcement *>(_payloadObject.get());
                 std::shared_ptr<Payload_Vehicle_Announcement> Payload =  std::dynamic_pointer_cast<Payload_Vehicle_Announcement>(_payloadObject);
              
                DOIPEntity FoundEntity;

                if(Payload->Payload.size() > 0)
                {
                    // DOIPSession::Instance->RespondedDOIPEntityCachedData.VIN = Payload->GetVIN();
                    // DOIPSession::Instance->RespondedDOIPEntityCachedData.EID = Payload->GetEID();
                    // DOIPSession::Instance->RespondedDOIPEntityCachedData.GID = Payload->GetGID();
                    // DOIPSession::Instance->RespondedDOIPEntityCachedData.LogicalAddress = Payload->GetlogicalAddress();
                    // DOIPSession::Instance->RespondedDOIPEntityCachedData.FurtherActions = Payload->GetFurtherAction();

                    FoundEntity.IPAddress = objResponse.EndPoint.IPAddress;
                    FoundEntity.Port = objResponse.EndPoint.Port;
                    FoundEntity.VIN = Payload->GetVIN();
                    FoundEntity.EID = Payload->GetEID();
                    FoundEntity.GID = Payload->GetGID();
                    FoundEntity.LogicalAddress = Payload->GetlogicalAddress();
                    FoundEntity.FurtherActions = Payload->GetFurtherAction();


                    
                    if(Payload->ValidationErrors.Messages.size() > 0)
                    {
                        retStatus = DIAGNOSTIC_STATUS::INTERNAL_ERROR;
                        return std::make_pair(retStatus, bufferResponse);
                    }
                    
                     DOIPAccessImplementation::Instance->ContextConvey->FoundDOIPEntity(FoundEntity);
                    
                    DOIPSession::Instance->RespondedDOIPEntityCachedData = DOIPEntity();
                    return std::make_pair(retStatus, bufferResponse);
                }
                else
                {
                    ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Vehicle Identification Response Payload"));
                    
                    return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
                }
            }
            else
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Vehicle Identification Response Object"));
                return std::make_pair(DIAGNOSTIC_STATUS::INTERNAL_ERROR, bufferResponse);
            }

        }

    
        int VehicleIdentificationDiagState::SendData(std::vector<uint8_t> data)
        {
            UDPBroadcast::Instance->UDPBroadcastPacket(data);

            if(UDPBroadcast::Instance->ValidationErrors.Messages.size() > 0)
            {
                return DIAGNOSTIC_STATUS::INTERNAL_ERROR;
            }
            else
            {
                return DIAGNOSTIC_STATUS::SUCCESS;
            }
        }

}