#pragma once

#include <stdint-gcc.h>
#include <string>
#include <vector>


#include "Framework/DataTypes/PAYLOAD_TYPES/Response_Payload_Types.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"
#include "Framework/DataTypes/Extras/IPEndPoint.h"


namespace fmBoip
{
    class DOIPResponseObject
    {
        //1 byte protocol version, 1-byte Invers protocol version
        //2 byte Payload Type, 4-bytes - Payload length
        
        public:
        static int Number_Of_Bytes_In_Header;
        IPEndPoint EndPoint;
        
         uint8_t ProtocolVersion = 0x00; //Should be read as 0xFF or 0x02
         uint8_t InverseProtocolVersion = 0x00;
        
         Response_Payload_Types::CODE Res_Payload_Type = Response_Payload_Types::DOIPTester_UNKNOWN_CODE;
         std::shared_ptr<PayloadObject> Payload;
         int PayloadLength = 0;
        

        //Returns standard header length in bytes
        static int GetHeaderLength();
        
        void SetProtocolVersion(uint8_t _ProtocolVersion);
        
        uint8_t GetProtocolVersion();
        
        void SetInverseProtocolVersion(uint8_t _InverseProtocolVersion);
        
        uint8_t GetInverseProtocolVersion();
        
        void SetPayloadType(Response_Payload_Types::CODE _Res_Payload_Type);
        
        Response_Payload_Types::CODE GetPayLoadType();
        
        void SetPayloadLength(int _PayloadLength);
    
        int GetPayloadLength();


        void SetPayload(std::shared_ptr<PayloadObject> _Payload);
        
        std::shared_ptr<PayloadObject> GetPayload();
    };
}                                                                                                                                                       