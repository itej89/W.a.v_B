#pragma once

#include <stdint-gcc.h>
#include <vector>


#include "Framework/DataTypes/PAYLOAD_TYPES/Request_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"


namespace fmBoip
{
    class DOIPRequestObject
    {
        //1 byte protocol version, 1-byte Invers protocol version
        //2 byte Payload Type, 4-bytes - Payload length
        
        private:
         static int Number_Of_Bytes_In_Header;
        
         uint8_t ProtocolVersion = 0xff;
         uint8_t InverseProtocolVersion = 0x00;
        
         Request_Payload_Types::CODE Req_Payload_Type;
         std::shared_ptr<PayloadObject> Payload;
        

        //Returns standard header length in bytes
        public:
        static int GetHeaderLength();
        
        void SetProtocolVersion(uint8_t _ProtocolVersion);
        
        uint8_t GetProtocolVersion();
        
        void SetInverseProtocolVersion(uint8_t _InverseProtocolVersion);
        
        uint8_t GetInverseProtocolVersion();
        
        void SetPayloadType(Request_Payload_Types::CODE _Req_Payload_Type);
        
        Request_Payload_Types::CODE GetPayLoadType();
        
        
        void SetPayload(std::shared_ptr<PayloadObject> _Payload);
        
        std::shared_ptr<PayloadObject> GetPayload();
        
    };
}