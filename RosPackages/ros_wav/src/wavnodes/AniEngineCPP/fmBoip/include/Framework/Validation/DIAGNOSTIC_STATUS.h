#pragma once

#include <map>
#include <string>



#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Activation_Response_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_Power_mode_Values.h"

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/Diagnostic_NAK_Codes.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/NAK_Codes.h"

namespace fmBoip
 {
  

  class DIAGNOSTIC_STATUS{
      public:
      enum CODE
      {
        COMPLETE,
        INTERNAL_ERROR,
        UDP_TIMEOUT,
        TCP_TIMEOUT,
        SUCCESS,
        DIAG_ACK_TIMEOUT,
        ACTIVATIOMN_CONFIRMATION_TIMEOUT,
        INVALID_HEADER,
        RESERVED_ISO13400,
        
        //Routing activation resposnse codes
        RA_RES_DENIED_UNKNOWN_SOURCE_ADDRESS,
        RA_RES_DENIED_ALL_SUPPORTED_SOCKETS_REGISTERED_AND_ACTIVE,
        RA_RES_DENIED_SOURCE_ADDRESS_MISMATCH,
        RA_RES_DENIED_SOURCE_ADDRESS_ACTIVE_OTHER_PORT,
        RA_RES_DENIED_MISSING_AUTHENTICATION,
        RA_RES_DENIED_REJECTED_CONFIRMATION,
        RA_RES_DENIED_UNSUPPORTED_ACTIVATION_TYPE,
        RA_RES_VEHICLE_MANUFACTURER_SPECIFIC,
        
        //generic NAK (header+diagnostic)
        MESSAGE_TOO_LARGE,
        OUT_OF_MEMORY,
        
        //generic header NACK codes
        NAK_INCORRECT_PATTERN,
        NAK_UNKNOWN_PAYLOAD,
        NAK_INVALID_PAYLOAD_LENGTH,
        
        //diagnostic message negative ackowledgement codes
        DIAG_NAK_UNKOWN_NETWORK,
        DIAG_NAK_INVALID_SOURCE_ADDRESS,
        DIAG_NAK_TARGET_UNREACHABLE,
        DIAG_NAK_TRANSPORT_PROTOCOL_ERROR,
        DIAG_NAK_UNKOWN_TARGET,
        
        //diagnostic power mode information codes
        DIAG_POWER_MODE_NOT_READY,
        DIAG_POWER_MODE_NOT_SUPPORTED,
        
        //uds status codes
        DIAG_RESPONSE_TIMEOUT,
        DIAG_RECONN_TIMEOUT,
        
        NO_RESPONSE,
        
        DIAG_PROGRESS
      };
    



    std::map<Activation_Response_Codes::CODE, int> ResponseCode_ErrorCode = {

        { Activation_Response_Codes::RA_RES_DENIED_ALL_SUPPORTED_SOCKETS_REGISTERED_AND_ACTIVE, RA_RES_DENIED_ALL_SUPPORTED_SOCKETS_REGISTERED_AND_ACTIVE },
        { Activation_Response_Codes::RA_RES_DENIED_MISSING_AUTHENTICATION, RA_RES_DENIED_MISSING_AUTHENTICATION },
        { Activation_Response_Codes::RA_RES_DENIED_REJECTED_CONFIRMATION, RA_RES_DENIED_REJECTED_CONFIRMATION },
        { Activation_Response_Codes::RA_RES_DENIED_SOURCE_ADDRESS_ACTIVE_OTHER_PORT, RA_RES_DENIED_SOURCE_ADDRESS_ACTIVE_OTHER_PORT },
        { Activation_Response_Codes::RA_RES_DENIED_SOURCE_ADDRESS_MISMATCH, RA_RES_DENIED_SOURCE_ADDRESS_MISMATCH },
        { Activation_Response_Codes::RA_RES_DENIED_UNKNOWN_SOURCE_ADDRESS, RA_RES_DENIED_UNKNOWN_SOURCE_ADDRESS },
        { Activation_Response_Codes::RA_RES_DENIED_UNSUPPORTED_ACTIVATION_TYPE, RA_RES_DENIED_UNSUPPORTED_ACTIVATION_TYPE },
        { Activation_Response_Codes::RA_RES_RESERVED_ISO13400, RESERVED_ISO13400 },
        { Activation_Response_Codes::RA_RES_VEHICLE_MANUFACTURER_SPECIFIC, RA_RES_VEHICLE_MANUFACTURER_SPECIFIC },
    };

    std::map<NAK_Codes::CODE, int> HeaderNACKCode_ErrorCode = {
        {NAK_Codes::NAK_INCORRECT_PATTERN, NAK_INCORRECT_PATTERN},
        {NAK_Codes::NAK_INVALID_PAYLOAD_LENGTH, NAK_INVALID_PAYLOAD_LENGTH},
        {NAK_Codes::NAK_MESSAGE_TOO_LARGE, MESSAGE_TOO_LARGE},
        {NAK_Codes::NAK_OUT_OF_MEMORY, OUT_OF_MEMORY},
        {NAK_Codes::NAK_RESERVED_ISO13400, RESERVED_ISO13400},
        {NAK_Codes::NAK_UNKNOWN_PAYLOAD, NAK_UNKNOWN_PAYLOAD}
    };
    

    std::map<Diagnostic_NAK_Codes::CODE, int> DiagNACKCode_ErrorCode = {
        {Diagnostic_NAK_Codes::DIAG_NAK_RESERVED_ISO13400, RESERVED_ISO13400},
    
        {Diagnostic_NAK_Codes::DIAG_NAK_INVALID_SOURCE_ADDRESS, DIAG_NAK_INVALID_SOURCE_ADDRESS},
        
        {Diagnostic_NAK_Codes::DIAG_NAK_UNKOWN_TARGET, DIAG_NAK_UNKOWN_TARGET},
        
        {Diagnostic_NAK_Codes::DIAG_NAK_MESSAGE_TOO_LARGE, MESSAGE_TOO_LARGE},
        
        {Diagnostic_NAK_Codes::DIAG_NAK_OUT_OF_MEMORY, OUT_OF_MEMORY},
        
        {Diagnostic_NAK_Codes::DIAG_NAK_TARGET_UNREACHABLE, DIAG_NAK_TARGET_UNREACHABLE},
        
        {Diagnostic_NAK_Codes::DIAG_NAK_UNKOWN_NETWORK, DIAG_NAK_UNKOWN_NETWORK},
        
        {Diagnostic_NAK_Codes::DAIG_NAK_TRANSPORT_PROTOCOL_ERROR, DIAG_NAK_TRANSPORT_PROTOCOL_ERROR}
 };
    
    std::map<Diagnostic_Power_mode_Values::CODE, int>  DiagPowerModeCode_ErrorCode = {
        {Diagnostic_Power_mode_Values::DIAG_POWER_MODE_NOT_READY, DIAG_POWER_MODE_NOT_READY},
        {Diagnostic_Power_mode_Values::DIAG_POWER_MODE_NOT_SUPPORTED, DIAG_POWER_MODE_NOT_SUPPORTED},
        {Diagnostic_Power_mode_Values::DIAG_POWER_MODE_RESERVED_ISO13400, RESERVED_ISO13400}
    };

             
    };

 }

