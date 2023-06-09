#pragma once 

#include <iterator>
#include <map>

#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "Framework/DataTypes/ActuatorCalibration.h"
#include "DataTypes/Constants/DB_Table_Columns.h"
#include "FrameworkImplementation/PublicTypes/Constants/KineticsEEPROM.h"

using std::map;

using fmDB::DB_Table_Columns;
using fmKinetics::Actuator;

namespace fmKinetics
{
     class MachineConfig
    {
        public:

           map<Actuator::etype, ActuatorCalibration*> MachineActuatorList = {
                    {Actuator::TURN, new ActuatorCalibration(Actuator::TURN, KineticsEEPROM::Referance_Angle_TURN, KineticsEEPROM::SHURDOWN_DELTA_TURN, KineticsEEPROM::Actuator_Address_TURN, DB_Table_Columns::SERVO_TURN)},
                    {Actuator::LIFT,  new ActuatorCalibration(Actuator::LIFT,  KineticsEEPROM::Referance_Angle_LIFT,KineticsEEPROM::SHURDOWN_DELTA_LIFT, KineticsEEPROM::Actuator_Address_LIFT,  DB_Table_Columns::SERVO_LIFT)},
                    {Actuator::LEAN  , new ActuatorCalibration( Actuator::LEAN,  KineticsEEPROM::Referance_Angle_LEAN, KineticsEEPROM::SHURDOWN_DELTA_LEAN, KineticsEEPROM::Actuator_Address_LEAN,  DB_Table_Columns::SERVO_LEAN)},
                    {Actuator::TILT  , new ActuatorCalibration( Actuator::TILT,  KineticsEEPROM::Referance_Angle_TILT, KineticsEEPROM::SHURDOWN_DELTA_TILT, KineticsEEPROM::Actuator_Address_TILT,  DB_Table_Columns::SERVO_TILT)}
            };


            static MachineConfig Instance;

            Actuator::etype getActuatorWith(int address);
    };

}