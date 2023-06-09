#pragma once


//EEPROM structure**********************

/*Calibration Data is stored from address Zero at 
  3 bytes per degree from 0 to SERVO_TOTAL_DEGREE degrees*/

/*SW Version stored at address locations 1016,1017,1018,1019*/
//EEPROM structure**********************


void VersionIntegrity()
{
  if(!(EEPROM.read(1016) == SWVer[0] && EEPROM.read(1017) == SWVer[1] && EEPROM.read(1018) == SWVer[2] && EEPROM.read(1019) == SWVer[3]))
  {
    EEPROM.write(1016,SWVer[0]); EEPROM.write(1017,SWVer[1]); EEPROM.write(1018,SWVer[2]); EEPROM.write(1019,SWVer[3]);
  }
}


void WriteServoCalibation(uint16_t Degree, uint16_t value)
{
  EEPROM.write((Degree*2),     (uint8_t)(value&0xFF));
  EEPROM.write((Degree*2)+1,   (uint8_t)((value>>8)&0xFF));
}
