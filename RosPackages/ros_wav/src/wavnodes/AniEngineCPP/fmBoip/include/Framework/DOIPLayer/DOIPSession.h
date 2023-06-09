#pragma once

#include <stdint-gcc.h>
#include <string>
#include <memory>

#include "Framework/DataTypes/Extras/IPEndPoint.h"
#include "Framework/DataTypes/ADDRESSING_TYPES.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"


namespace fmBoip
 {

    class DOIPSession {

        public:
        static std::string NLOG_LOGGER_NAME;
    
        ADDRESSING_TYPES::MessageType DaignosticMessageType  = ADDRESSING_TYPES::PHYSICAL;
        ADDRESSING_TYPES::MessageType TesterPresentMessageType = ADDRESSING_TYPES::FUNCTIONAL;
    
        ADDRESSING_TYPES::UDSRequestType UDSRequestType = ADDRESSING_TYPES::TESTER_PRESENT;
    
     static std::unique_ptr<DOIPSession> Instance;
    
   
    
      std::vector<std::vector<uint8_t>> InvalidAddresses;
    
   
    
     std::vector<uint8_t> ValidProtocolVersions;

      
    
    std::vector<uint8_t>  ValidFurtherActions;

   
    
    IPEndPoint  RemoteEndPoint;
    
     int LOCAL_TCP_PORT = 13400;
     int LOCAL_UDP_PORT = 13400;
    
    uint8_t  DefaultProtocolVersion = 0xFF;

    uint8_t  ProtocolVersion = 0x01;

    
    uint8_t  FurtherAction = 0x00;
    
    std::vector<uint8_t> TargetAddress{0x00, 0x00};
    
    
    uint8_t  DiagnosticSessionSID = 0x10;
    uint8_t  DefaultDiagSessionLID = 0x01;
    uint8_t  ECUResetSID = 0x11;
    
    
    std::vector<uint8_t>  LastDiagnosticResponseData;
    
    DOIPEntity RespondedDOIPEntityCachedData;
    

    uint8_t  InverseProtocolVersion();
    
    std::vector<std::vector<uint8_t>> getInvalidAddresses() ;
    
    std::vector<uint8_t>  getValidProtocolVersions();

    std::vector<uint8_t>  getValidFurtherActions();
    
    uint8_t  DefaultInverseProtocolVersion();

    void ResetSession();

    };

}
