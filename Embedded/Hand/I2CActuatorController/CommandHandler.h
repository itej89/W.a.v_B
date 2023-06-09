#pragma once

#include "PrintHandler.h"
#include "EEPROMMap.h"
#include "GlobalConfiguration.h"
#include "Registers.h"
#include "GlobalContext.h"


void perform_calibration(){
      servo_motor.write(0);
        delay(3000);
        
        DEBUG_PRINT_STRING("Started Calibrating Servo\n");
      for(int i=0; i<SERVO_TOTAL_DEGREE; i++){
        servo_motor.write(map(i, 0, SERVO_TOTAL_DEGREE, 0, 180)); 
        delay(1000);

          uint16_t sensorValue =  analogRead(SERVO_POT_PIN);
          DEBUG_PRINT_VALUE(i);
          DEBUG_PRINT_STRING(" : ");
          DEBUG_PRINT_VALUE(sensorValue);
          DEBUG_PRINT_STRING("\n");

          WriteServoCalibation(i, sensorValue);
      }
      
      servo_motor.write(90);
      delay(1000);
}


void check_calibration_request(){  
  if(_COMMAND_REGISTERS->CAL){perform_calibration();                        _COMMAND_REGISTERS->CAL=CLEAR;  DEBUG_PRINT_STRING("Calibrating Servo\n");}
  }


void serve_command(){
  
  if(_COMMAND_REGISTERS->ATTACH_PWM)  {servo_motor.attach(SERVO_PWM_PIN);  _COMMAND_REGISTERS->ATTACH_PWM=CLEAR;    DEBUG_PRINT_STRING("Servo Attached\n");}
  else 
  if(_COMMAND_REGISTERS->DETACH_PWM)  {servo_motor.detach();               _COMMAND_REGISTERS->DETACH_PWM=CLEAR;    DEBUG_PRINT_STRING("Servo Detached\n");}
    
  if(_COMMAND_REGISTERS->ATTACH_POWER){digitalWrite(SERVO_POWER_PIN, HIGH);    _COMMAND_REGISTERS->ATTACH_POWER=CLEAR;  DEBUG_PRINT_STRING("Servo Power On\n");}
  else 
  if(_COMMAND_REGISTERS->DETACH_POWER){digitalWrite(SERVO_POWER_PIN, LOW);     _COMMAND_REGISTERS->DETACH_POWER=CLEAR;  DEBUG_PRINT_STRING("Servo Power Off\n");}
  
  if(_COMMAND_REGISTERS->TRIGGER){
    

        DEBUG_PRINT_STRING("Recieved trigger");
      if(is_data_register_new())
        TRIGGER_REQUEST_COUNT++;
      else
        DEBUG_PRINT_STRING("No new data for motion");
        
        _COMMAND_REGISTERS->TRIGGER = CLEAR;
    }
}
