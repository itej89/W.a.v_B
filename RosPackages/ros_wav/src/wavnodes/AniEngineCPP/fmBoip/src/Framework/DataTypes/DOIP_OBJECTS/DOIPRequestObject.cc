
#include<vector>
#include<map>

#include "Framework/DataTypes/DOIP_OBJECTS/DOIPRequestObject.h"

namespace fmBoip
{
        int DOIPRequestObject::Number_Of_Bytes_In_Header = 8;

          int DOIPRequestObject::GetHeaderLength()
        {
            return DOIPRequestObject::Number_Of_Bytes_In_Header;
        }
        
        void DOIPRequestObject::SetProtocolVersion(uint8_t _ProtocolVersion)
        {
            ProtocolVersion = _ProtocolVersion;
            SetInverseProtocolVersion(ProtocolVersion^0xFF);
        }
        
        uint8_t DOIPRequestObject::GetProtocolVersion() 
        {
            return ProtocolVersion;
        }
        
        void DOIPRequestObject::SetInverseProtocolVersion(uint8_t _InverseProtocolVersion)
        {
            InverseProtocolVersion = _InverseProtocolVersion;
        }
        
        uint8_t DOIPRequestObject::GetInverseProtocolVersion()
        {
            return InverseProtocolVersion;
        }
        
        void DOIPRequestObject::SetPayloadType(Request_Payload_Types::CODE _Req_Payload_Type)
        {
            Req_Payload_Type = _Req_Payload_Type;
        }
        
        Request_Payload_Types::CODE DOIPRequestObject::GetPayLoadType()
        {
            return Req_Payload_Type;
        }
        

        void DOIPRequestObject::SetPayload(std::shared_ptr<PayloadObject> _Payload)
        {
            Payload = _Payload;
        }
        
        std::shared_ptr<PayloadObject> DOIPRequestObject::GetPayload()
        {
            return Payload;
        }
}