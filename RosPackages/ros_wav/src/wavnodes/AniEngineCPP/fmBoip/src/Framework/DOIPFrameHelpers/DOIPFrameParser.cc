#include <algorithm>

#include <VectorX.h>

#include "Framework/DOIPFrameHelpers/DOIPFrameParser.h"
#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"

namespace fmBoip
{
     bool DOIPFrameParser::Parse(std::vector<uint8_t> DOIPFrame, DOIPResponseObject& responseObject)
    {
        if(DOIPFrame.size() < DOIPResponseObject::GetHeaderLength())
        {
            return false;
        }
        else
        {
            responseObject.SetProtocolVersion(DOIPFrame[0]);
            responseObject.SetInverseProtocolVersion(DOIPFrame[1]);
            
            fmCommon::VectorX VecX;
            std::vector<uint8_t> PayloadTypeBytes = VecX.subvector(DOIPFrame, 2, 3);
            responseObject.SetPayloadType(Response_Payload_Types::Instance->DECODE(PayloadTypeBytes));
            responseObject.SetProtocolVersion(DOIPFrame[0]);
        
            if(responseObject.GetPayLoadType() != Response_Payload_Types::DOIPTester_UNKNOWN_CODE)
            {
                std::vector<uint8_t> LengthBytes = VecX.subvector(DOIPFrame, 4, 7);
                std::reverse(LengthBytes.begin(), LengthBytes.end());
                int payloadLength = GetLengthFromBytes(LengthBytes);
                responseObject.SetPayloadLength(payloadLength);
                
                if(payloadLength > 0 && payloadLength + DOIPResponseObject::Number_Of_Bytes_In_Header <= DOIPFrame.size())
                {
                    std::vector<uint8_t>  PayloadBytes = VecX.subvector(DOIPFrame, 8, DOIPFrame.size()-1);
                    
                    Response_Payload_Type_To_Object responeToPayloadObject;
                    std::shared_ptr<PayloadObject> responsePayload = responeToPayloadObject.GetPayloadObjectOfType(responseObject.GetPayLoadType(), PayloadBytes);
                    responseObject.SetPayload(responsePayload);
                }
            }
            
            return true;
        
            }
        }
        
        int DOIPFrameParser::GetLengthFromBytes(std::vector<uint8_t> bytes)
        {
            int value = 0;
            for(int i=0 ; i< bytes.size(); i++)
            {
                int shiftCount = 8 * i;
                value = value + (((bytes[i] & 0xFF) << shiftCount));
            }
            return value;
        }
}