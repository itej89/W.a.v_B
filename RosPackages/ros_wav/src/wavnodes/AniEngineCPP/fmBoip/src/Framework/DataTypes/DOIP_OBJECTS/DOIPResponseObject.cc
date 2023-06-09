#include<vector>
#include<map>

#include "Framework/DataTypes/DOIP_OBJECTS/DOIPResponseObject.h"

namespace fmBoip
{
      int DOIPResponseObject::Number_Of_Bytes_In_Header = 8;
        //Returns standard header length in bytes
        int DOIPResponseObject::GetHeaderLength()
        {
            return DOIPResponseObject::Number_Of_Bytes_In_Header;
        }
        
        void DOIPResponseObject::SetProtocolVersion(uint8_t _ProtocolVersion)
        {
            ProtocolVersion = _ProtocolVersion;
        }
        
        uint8_t DOIPResponseObject::GetProtocolVersion()
        {
            return ProtocolVersion;
        }
        
        void DOIPResponseObject::SetInverseProtocolVersion(uint8_t _InverseProtocolVersion)
        {
            InverseProtocolVersion = _InverseProtocolVersion;
        }
        
        uint8_t DOIPResponseObject::GetInverseProtocolVersion()
        {
            return InverseProtocolVersion;
        }
        
        void DOIPResponseObject::SetPayloadType(Response_Payload_Types::CODE _Res_Payload_Type)
        {
             Res_Payload_Type = _Res_Payload_Type;
        }
        
        Response_Payload_Types::CODE DOIPResponseObject::GetPayLoadType()
        {
            return Res_Payload_Type;
        }
        
         void DOIPResponseObject::SetPayload(std::shared_ptr<PayloadObject> _Payload)
        {
            Payload = _Payload;
        }
        
        std::shared_ptr<PayloadObject> DOIPResponseObject::GetPayload()
        {
            return Payload;
        }

        void DOIPResponseObject::SetPayloadLength(int _PayloadLength)
        {
            PayloadLength = _PayloadLength;
        }

        int DOIPResponseObject::GetPayloadLength()
        {
            return PayloadLength;
        }

}