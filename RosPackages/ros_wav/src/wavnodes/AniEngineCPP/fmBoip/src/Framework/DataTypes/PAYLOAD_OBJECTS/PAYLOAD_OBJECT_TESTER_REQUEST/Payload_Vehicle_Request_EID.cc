
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Vehicle_Request_EID.h"

namespace fmBoip
 {
        void Payload_Vehicle_Request_EID::initialize_PayloadItems()
        {
            Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::EID, Payload_Item_Type(0, 6)));
        }
        
        Payload_Vehicle_Request_EID::Payload_Vehicle_Request_EID() {
            initialize_PayloadItems();
        }
        
        Payload_Vehicle_Request_EID::Payload_Vehicle_Request_EID(std::vector<uint8_t> DOIPPayload) {
            initialize_PayloadItems();
            Decode_Payload(DOIPPayload);
        }
        
        void Payload_Vehicle_Request_EID::SetEID(std::vector<uint8_t> EID)
        {
            Payload.at(PayloadObject::EID).RawData.insert(Payload.at(PayloadObject::EID).RawData.end(),
            EID.begin(), EID.end());
        }
 }