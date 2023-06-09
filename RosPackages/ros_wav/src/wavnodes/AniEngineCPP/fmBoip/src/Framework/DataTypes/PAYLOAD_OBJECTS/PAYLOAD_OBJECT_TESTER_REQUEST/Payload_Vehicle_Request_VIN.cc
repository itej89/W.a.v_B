
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/Payload_Vehicle_Request_VIN.h"

namespace fmBoip
 {
   void Payload_Vehicle_Request_VIN::initialize_PayloadItems()
    {
        Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::VIN, Payload_Item_Type(0, 17)));
    }
    
     Payload_Vehicle_Request_VIN::Payload_Vehicle_Request_VIN() {
        initialize_PayloadItems();
    }
    
      Payload_Vehicle_Request_VIN::Payload_Vehicle_Request_VIN(std::vector<uint8_t> DOIPPayload) {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    void Payload_Vehicle_Request_VIN::SetVIN(std::vector<uint8_t> VIN)
    {
        Payload.at(PayloadObject::VIN).RawData.insert(Payload.at(PayloadObject::VIN).RawData.end(),
        VIN.begin(), VIN.end());
    }
 }