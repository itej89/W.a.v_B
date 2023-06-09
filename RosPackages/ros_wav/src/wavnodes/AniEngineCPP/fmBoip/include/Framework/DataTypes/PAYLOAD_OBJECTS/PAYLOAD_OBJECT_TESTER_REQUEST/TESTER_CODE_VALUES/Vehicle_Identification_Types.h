#pragma once 

#include <memory>

#include <stdint-gcc.h>
#include <map>


 namespace fmBoip
{

class Vehicle_Identification_Types
{   

    public:
    static std::unique_ptr<Vehicle_Identification_Types> Instance;

    enum CODE
    {
         VEHICLE_IDENTIFICATION,
         VEHICLE_IDENTIFICATION_VIN,
         VEHICLE_IDENTIFICATION_EID
    };

    std::map<uint8_t, CODE> VALUE_TO_CODE; 

    Vehicle_Identification_Types();

    bool IsIdentificationMode(uint8_t Mode);
    
    CODE DECODE(uint8_t Vehicle_Identification_Value);
};

}