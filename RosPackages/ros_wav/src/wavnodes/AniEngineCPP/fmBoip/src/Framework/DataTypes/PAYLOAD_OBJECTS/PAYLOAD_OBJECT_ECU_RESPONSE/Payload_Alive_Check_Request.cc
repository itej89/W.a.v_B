
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Alive_Check_Request.h"


namespace fmBoip
 {
   void Payload_Alive_Check_Request::initialize_PayloadItems()
        {
           Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::SOURCE_ADDRESS, Payload_Item_Type(0, 2)));
        }

    Payload_Alive_Check_Request::Payload_Alive_Check_Request()
        {
            initialize_PayloadItems();
        }
    
      Payload_Alive_Check_Request::Payload_Alive_Check_Request(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload( DOIPPayload);
    }
    
       void  Payload_Alive_Check_Request::SetSourceAddress(std::vector<uint8_t>  SA)
        {
            Payload.at(SOURCE_ADDRESS).RawData.insert(Payload.at(SOURCE_ADDRESS).RawData.end(),
            SA.begin(), SA.end());
        }
    
 }