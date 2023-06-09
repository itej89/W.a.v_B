#pragma once

//Preprocessor to enable debug messages
#define ENABLE_DEBUG_MESSAGES 1


/*SW Version stored at address locations 1016,1017,1018,1019*/
byte SWVer[] = {1,1,0,0}; 


#define SERVO_TOTAL_DEGREE 270

#define I2C_ADDRESS 7
//PIN CONFIGURATION
#define SERVO_POWER_PIN 7
#define SERVO_PWM_PIN 10
#define SERVO_POT_PIN A6

//I2C Base address for Status registers
#define STATUS_REGISTER_BASE_ADDRESS 0x10
#define STATUS_REGISTER_SIZE 5

//I2C Base address for Data registers
#define DATA_REGISTER_BASE_ADDRESS 0x30
#define DATA_REGISTER_SIZE 14


//I2C Base address for Data registers
#define COMMAND_REGISTER_BASE_ADDRESS 0x90
#define COMMAND_REGISTER_SIZE 6

//I2C Base address for Data registers
#define EEROM_REGISTER_BASE_ADDRESS 0xE0
#define EEROM_REGISTER_SIZE 4096


//Maximum time for transmitting a single commnd from I2C master before transmission reset
#define MAX_I2C_COMMAND_TRANSMISSION_TIME_MS 5000

//Maximum time for transmitting first wo bytes of a single commnd from I2C master
#define MAX_I2C_COMMAND_BYTE_TRANSMISSION_TIME_MS 1000
