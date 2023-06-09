

/*
  Include library headers
*/
#include <MsTimer2.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>


/*
 * Configuration file for the current actuator
 */ 
#include "GlobalConfiguration.h"


/*
  Include Custom types and objects
*/
#include "EEPROMMap.h"
#include "Registers.h"
#include "EasingFunctions.h"
#include "GlobalContext.h"
#include "MotionHandler.h"


/*
  Include Event handlers and helper functions
*/
#include "I2CEventHandlers.h"




void intilize(){

    //Initialize Serial interface*********************************************************
    Serial.begin(115200);
    //************************************************************************************


    //Initialize I2C interface**********************************************************
    Wire.begin(I2C_ADDRESS);                // join i2c bus with address #8
    TWAR = (I2C_ADDRESS<<1)|1;
    Wire.onReceive(receiveEvent); // register event from "I2CEventHandlers.h"
    Wire.onRequest(requestEvent); // register event from "I2CEventHandlers.h"
    //************************************************************************************


    //Initialize GPIO pins**************************************************************
    pinMode(3, INPUT);
    pinMode(SERVO_POWER_PIN, OUTPUT);
    pinMode(8, OUTPUT);
    digitalWrite(SERVO_POWER_PIN, LOW);
    digitalWrite(8, LOW);
    //************************************************************************************


    //sample servo pot reading************************************************************
     analogRead(SERVO_POT_PIN);
     analogRead(SERVO_POT_PIN);
     analogRead(SERVO_POT_PIN);
    //************************************************************************************



   //Initilaize Timer 2 Interrupt for 1ms************************************************
   // Just initializes. It wont start Timer2
    MsTimer2::set(1, SetEasingTime_ms);
   //************************************************************************************
  
}



void setup() {
  
  VersionIntegrity();

  //Initialize controller modules
  intilize();
}






void loop() {
 handle_motion_requests();
}
