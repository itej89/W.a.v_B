#include <algorithm> 

#include "Framework/DOIPFrameHelpers/DOIPFrameSynthesizer.h"

namespace fmBoip
{
 std::vector<uint8_t> DOIPFrameSynthesizer::CreateDOIPFrame(DOIPRequestObject& DOIPObject)
        {
                std::vector<uint8_t>  DOIPFrame;
                
                
                    int32_t PayloadLength = 0;
                    std::vector<uint8_t> DOIPPayload;
                    
                    if(DOIPObject.GetPayload() != nullptr)
                    {
                        PayloadLength = DOIPObject.GetPayload()->TotalNumberOfBytesInPayload();
                        
                        if(PayloadLength > 0)
                        {
                            DOIPPayload = DOIPObject.GetPayload()->Make_Payload();
                        }
                        else
                        {
                            return DOIPFrame;
                        }
                    }
                    else
                    {
                        //DOIPFrame = [UInt8](repeating: 0, count: DOIPRequestObject.GetHeaderLength())
                    }
                    
                    
                    DOIPFrame.push_back(DOIPObject.GetProtocolVersion());
                    DOIPFrame.push_back(DOIPObject.GetInverseProtocolVersion());
                    
                    std::vector<uint8_t> PayloadTypeArray = Request_Payload_Types::Instance->Encode(DOIPObject.GetPayLoadType());
                    std::reverse(PayloadTypeArray.begin(), PayloadTypeArray.end());
                    
                    std::vector<uint8_t> PayloadLengthArray = Request_Payload_Types::Instance->toBytes(PayloadLength);
                    std::reverse(PayloadLengthArray.begin(), PayloadLengthArray.end());
                    
                    DOIPFrame.insert(DOIPFrame.end(), PayloadTypeArray.begin(), PayloadTypeArray.end());
                    DOIPFrame.insert(DOIPFrame.end(), PayloadLengthArray.begin(), PayloadLengthArray.end());
                    
                    if(DOIPPayload.size() > 0)
                    {
                        DOIPFrame.insert(DOIPFrame.end(), DOIPPayload.begin(), DOIPPayload.end());
                    }
                
                    
                return DOIPFrame;
            }


         
             DOIPRequestObject DOIPFrameSynthesizer::FormHeaderForDoIPFrame(Request_Payload_Types::CODE payloadType)
            {
                 DOIPRequestObject request;
                if(payloadType == Request_Payload_Types::PLD_VEH_IDEN_REQ ||
                    payloadType == Request_Payload_Types::PLD_VEH_IDEN_REQ_VIN ||
                    payloadType == Request_Payload_Types::PLD_VEH_IDEN_REQ_EID)
                {
                    request.SetProtocolVersion(DOIPSession::Instance->DefaultProtocolVersion);
                }
                else
                {
                    request.SetProtocolVersion(DOIPSession::Instance->ProtocolVersion);
                }
                
                request.SetPayloadType(payloadType);
                return request;
            }
}