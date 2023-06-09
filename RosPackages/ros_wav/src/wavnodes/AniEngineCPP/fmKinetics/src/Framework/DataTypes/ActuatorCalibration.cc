#include "Framework/DataTypes/ActuatorCalibration.h"


namespace fmKinetics
{
     ActuatorCalibration::ActuatorCalibration(Actuator actuatorType, KineticsEEPROM::EEPROMParameter eepromRefAngleLocation, KineticsEEPROM::EEPROMParameter shutdownAngleAddressLocationInEERPOM, KineticsEEPROM::EEPROMParameter eepromAddressLocation, DB_Table_Columns::DBTables calibrationStore) 
      {
        ActuatorType = actuatorType;
        RefAngleAddressLocationInEERPOM = eepromRefAngleLocation;
        ActuatorAddressLocationInEERPOM = eepromAddressLocation;
        ShutdownAngleAddressLocationInEERPOM = shutdownAngleAddressLocationInEERPOM;
        CalibrationStoreName = calibrationStore;
    }

}