#pragma once

#include <string>
#include <map>
#include <limits>

#include "VectorX.h"

#include "Framework/Validation/interface/IValidation.h"
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Item_Type.h"

namespace fmBoip
{
    class PayloadObject : public IValidation
    {
    public:

     enum TAG
    {
        ISO_RESERVED,OEM_RESERVED,
        
        //Vehicle Identification REsponse Payload
        VIN,LOGICAL_ADDRESS,EID,GID,FURTHER_ACTION,VIN_GID,SYNC,
        
        //Routing Activation Request Payload
        SOURCE_ADDRESS, ACTIVATION_TYPE,//ISO_RESERVED,OEM_RESERVED,
        
        //Routing Activation response Payload
        LOGICAL_ADDRESS_TEST_EQUIPMENT,LOGICAL_ADDRESS_DOIP_ENTITY,ROUTING_ACTIVATION_RESPONSE_CODE,//ISO_RESERVED,OEM_RESERVED,
        
        //Diagnostic Message Request/Response Payload
        TARGET_ADDRESS,USER_DATA,//SOURCE_ADDRESS,TARGET_ADDRESS,ACK,PREVIOUS_DIAGNOSTIC_DATA
        
        //Diagnostic Message Positive Acknowledgement Payload
        ACK,PREVIOUS_DIAGNOSTIC_DATA,//SOURCE_ADDRESS,TARGET_ADDRESS_ACK,ACK,PREVIOUS_DIAGNOSTIC_DATA,
        
        //Diagnostic Message Negative Acknowledgement Payload
        NACK,//SOURCE_ADDRESS,TARGET_ADDRESS_ACK,ACK,PREVIOUS_DIAGNOSTIC_DATA,
        
        //Alive Check Request
        //No Payload
        
        //Diagnostic Power Modez 
        //No Payload
        
        //Diagnostic Power Mode Response
        DIAGNOSTIC_POWER_MODE,
        
        //Diagnostic Status Request
        //Node Payload
        
        //Diagnostic Status Response
        NODE_TYPE,MAX_CONCURRENT_TCP_SOCKETS,CURRENT_OPEN_TCP_SOCKETS,MAX_DATA_SIZE,
        
        //Generic HEader NACK
        HEADER_NACK
        
    };

    static uint32_t Max_DOIP_PAYLOAD_SIZE;

    uint64_t Minimum_Payload_Length_In_Bytes = 0;

    uint64_t Maximum_Payload_Length_In_Bytes = 0;

    std::map<TAG, Payload_Item_Type> Payload;
    
    
    //Calculate Payload Length according to the length specified in doip standard ISO 13400-2
    uint64_t DOIPPayloadMinimumLengthInBytes();
    
    uint64_t TotalNumberOfBytesInPayload();
    
    void ExtractPayload(std::vector<uint8_t> DOIPPayload);
    
    void Decode_Payload(std::vector<uint8_t> DOIPPayload);
    
  
    std::vector<uint8_t> Make_Payload();
  
    virtual  void initialize_PayloadItems();

    };
}