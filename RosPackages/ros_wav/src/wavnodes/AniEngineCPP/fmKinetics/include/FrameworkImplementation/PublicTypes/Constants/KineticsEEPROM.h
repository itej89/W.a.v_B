#pragma once 

#include <map>

#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"

using std::map;

namespace fmKinetics
{
     class KineticsEEPROM
    {
        public:
            enum EEPROMParameter : int
            {   
                Referance_Angle_TURN,
                Referance_Angle_LIFT,
                Referance_Angle_LEAN,
                Referance_Angle_TILT,
                Referance_Angle_LOCK_RIGHT,
                Referance_Angle_LOCK_LEFT,
                Actuator_Address_TURN,
                Actuator_Address_LIFT,
                Actuator_Address_LEAN,
                Actuator_Address_TILT,
                Actuator_Address_LOCK_RIGHT,
                Actuator_Address_LOCK_LEFT,
                SHURDOWN_DELTA_TURN,
                SHURDOWN_DELTA_LIFT,
                SHURDOWN_DELTA_LEAN,
                SHURDOWN_DELTA_TILT
            };

           map<EEPROMParameter, EEPROMDetails*> MEMORY_MAP = {
                    {EEPROMParameter::Referance_Angle_TURN, new EEPROMDetails(0, 1)},
                    {EEPROMParameter::Referance_Angle_LIFT,  new EEPROMDetails(1, 1)},
                    {EEPROMParameter::Referance_Angle_LEAN  , new EEPROMDetails( 2,  1)},
                    {EEPROMParameter::Referance_Angle_TILT  , new EEPROMDetails( 3,  1)},
                    {EEPROMParameter::Referance_Angle_LOCK_RIGHT  , new EEPROMDetails( 4,  1)},
                    {EEPROMParameter::Referance_Angle_LOCK_LEFT  , new EEPROMDetails( 5,  1)},
                    {EEPROMParameter::Actuator_Address_TURN , new EEPROMDetails( 6,  1)},
                    {EEPROMParameter::Actuator_Address_LIFT , new EEPROMDetails( 7,  1)},
                    {EEPROMParameter::Actuator_Address_LEAN , new EEPROMDetails( 8,  1)},
                    {EEPROMParameter::Actuator_Address_TILT , new EEPROMDetails(9,  1)},
                    {EEPROMParameter::Actuator_Address_LOCK_RIGHT , new EEPROMDetails( 10,  1)},
                    {EEPROMParameter::Actuator_Address_LOCK_LEFT , new EEPROMDetails( 11,  1)},
                    {EEPROMParameter::SHURDOWN_DELTA_TURN , new EEPROMDetails( 12,  2, true)},
                    {EEPROMParameter::SHURDOWN_DELTA_LIFT , new EEPROMDetails(14,  2, true)},
                    {EEPROMParameter::SHURDOWN_DELTA_LEAN , new EEPROMDetails( 16,  2, true)},
                    {EEPROMParameter::SHURDOWN_DELTA_TILT , new EEPROMDetails( 18,  2, true)}
                };
};

}