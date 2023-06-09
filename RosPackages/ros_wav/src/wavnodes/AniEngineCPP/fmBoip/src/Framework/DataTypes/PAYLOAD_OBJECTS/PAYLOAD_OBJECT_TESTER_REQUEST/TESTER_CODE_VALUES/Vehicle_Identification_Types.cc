
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/TESTER_CODE_VALUES/Vehicle_Identification_Types.h"

namespace fmBoip
 {

         
         std::unique_ptr<Vehicle_Identification_Types> Vehicle_Identification_Types::Instance(new Vehicle_Identification_Types());
         
      Vehicle_Identification_Types::Vehicle_Identification_Types()
    {
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x01, VEHICLE_IDENTIFICATION));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x02, VEHICLE_IDENTIFICATION_EID));
        VALUE_TO_CODE.insert(std::make_pair<uint8_t, CODE>(0x03, VEHICLE_IDENTIFICATION_VIN));
    }

    bool Vehicle_Identification_Types::IsIdentificationMode(uint8_t Mode)
    {
        return (VALUE_TO_CODE.find(Mode) != VALUE_TO_CODE.end());
    }
    
    Vehicle_Identification_Types::CODE Vehicle_Identification_Types::DECODE(uint8_t Vehicle_Identification_Value)
    {
       if(VALUE_TO_CODE.find(Vehicle_Identification_Value) != VALUE_TO_CODE.end())
        {
            return VALUE_TO_CODE.at(Vehicle_Identification_Value);
        }
        else
        {
            return VEHICLE_IDENTIFICATION;
        }
    }
}