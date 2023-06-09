
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Alive_Check_Response.h"

namespace fmBoip
 {
    void Payload_Alive_Check_Response::initialize_PayloadItems()
        {
            Payload.insert(std::make_pair<TAG,Payload_Item_Type>(PayloadObject::SOURCE_ADDRESS, Payload_Item_Type(0, 2)));
        }
        
        Payload_Alive_Check_Response::Payload_Alive_Check_Response() {
            initialize_PayloadItems();
        }
        
        Payload_Alive_Check_Response::Payload_Alive_Check_Response(std::vector<uint8_t> DOIPPayload) {
            initialize_PayloadItems();
            Decode_Payload(DOIPPayload);
        }

        void Payload_Alive_Check_Response::SetSourceAddress(std::vector<uint8_t> SA)
        {
            Payload.at(PayloadObject::SOURCE_ADDRESS).RawData.insert(Payload.at(PayloadObject::EID).RawData.end(),
            SA.begin(), SA.end());
        }
}