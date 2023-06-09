#pragma once 

#include <stdint-gcc.h>
#include <string>
#include <vector>
#include <memory>

#include "Framework/DataTypes/Extras/IPEndPoint.h"

 namespace fmBoip
{
    class DOIPParameters
    {   
        public:
        static std::unique_ptr<DOIPParameters> Instance;
    
        std::string DOIP_Entity_IPAddress = "255.255.255.255";
        int DOIP_ENTITY_UDP_DISCOVER = 13400;
        
        std::string Tester_IPAddress = "";
        int TESTER_UDP_PORT = 13401;
        
        std::vector<uint8_t> TesterAddress {0x0E, 0x8D};
        
        std::vector<uint8_t>  VIN {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        std::vector<uint8_t>  EID{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        
        
        int32_t  A_Doip_ctrl = 10000;
        
        uint8_t DOIP_DEFAULT_PROTOCOL = 0xFF;
        uint8_t DOIP_IDENTIFICATION_MODE = 0x01;
        
        
        int DiagPowerModeSupported = 0;
        int DoIPEntityStatusSupported = 0;
        
        
        std::vector<uint8_t> A_DOIP_Activation_Request_OEM_SPECIFIC {0x00, 0x00, 0x00, 0x00};
        std::vector<uint8_t>  A_DOIP_Activation_Request_ISO_RESERVED {0x00, 0x00, 0x00, 0x00};
        
        int Activation_Request_OEM_BYTES_ENABLED = 1;
        


        int32_t A_Processing_Time = 13400;
        int32_t DOIP_ACTIVATION_CONFIRMATION_REPEAT_TIME = 3000;
        int32_t DOIP_ACTIVATION_CONFIRMATION_REPEAT_COUNT = 20;
        
        int32_t DOIP_TCP_RESPONSE_WAIT_TIME = 5000;
        int32_t DOIP_TCP_RECONNECT_WAIT_TIME = 5000;
        
        int32_t A_Doip_Diagnostic_Message = 5000;
        int32_t DOIP_DIAG_NO_ACK_REPEAT_NUM = 2;
        uint32_t RoutingActivationType = 0x00;
        
        

        int32_t Nrc21or23RepeatCount = 3;
        
        int32_t P6Client = 5000;
        int32_t P3ClientPhys = 5000;
        int32_t P6ClientResponsePending = 5000;
        
        int ResponsePendingResponse = 0x7F0078;
        int ResponsePendingMask = 0xFF00FF;
        
        std::vector<uint8_t> FunctionaTargetAddress {0xe4, 0x00};
        int32_t P3ClientFunc = 5000;
        
        int32_t CycleTime = 2000;
        
        std::vector<uint8_t> TxData {0x3E};
        
        std::vector<uint8_t> TesterPresentTargetAddress {0xe4, 0x00};
        std::vector<uint8_t> RxData {0x7E};
        std::vector<uint8_t> RxMask {0xFF};
        
        int nrc21 = 0x7f0021;
        int nrc23 = 0x7f0023;
        
        int nrcMask = 0xff00ff;
    
    };

}