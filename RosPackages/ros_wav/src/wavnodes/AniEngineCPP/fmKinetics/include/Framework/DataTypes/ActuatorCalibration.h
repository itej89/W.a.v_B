#pragma once 

#include "FrameworkImplementation/PublicTypes/Constants/KineticsEEPROM.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "DataTypes/Constants/DB_Table_Columns.h"

using fmDB::DB_Table_Columns;

namespace fmKinetics
{
     class ActuatorCalibration {
    public:
     Actuator ActuatorType;
     int Address = 0;
     int RefPosition;
     int ShutdownDeltaAngle;
     KineticsEEPROM::EEPROMParameter RefAngleAddressLocationInEERPOM;
     KineticsEEPROM::EEPROMParameter ActuatorAddressLocationInEERPOM;
     KineticsEEPROM::EEPROMParameter ShutdownAngleAddressLocationInEERPOM;
     DB_Table_Columns::DBTables CalibrationStoreName;

      ActuatorCalibration(Actuator actuatorType, KineticsEEPROM::EEPROMParameter eepromRefAngleLocation, KineticsEEPROM::EEPROMParameter shutdownAngleAddressLocationInEERPOM, KineticsEEPROM::EEPROMParameter eepromAddressLocation, DB_Table_Columns::DBTables calibrationStore) ;
};
}