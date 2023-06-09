#pragma once

#include "GlobalConfiguration.h"

#define SET 1
#define CLEAR 0

/*
 * Type of Register Blocks available 
 */
 
enum REGISTER_BLOCK_TYPES {STATUS=0, DATA, COMMAND, EEROM, INVALID_BLOCK};


/*
 * Registers to store status of the actuator
 */
unsigned char STATUS_REGISTER_BUFFER[STATUS_REGISTER_SIZE];
typedef struct STATUS_REGISTER_STRUCTURE
{
    unsigned int SERVO_POWER_STATUS:8;  //Relative address from base: 0
    unsigned int SERVO_PWM_STATUS:8;    //Relative address from base: 1
    unsigned int SERVO_MOTION_STATUS:8; //Relative address from base: 2
    
    unsigned int CURRENT_ANGLE:16;      //Relative address from base: 3
};

STATUS_REGISTER_STRUCTURE *_STATUS_REGISTERS = (STATUS_REGISTER_STRUCTURE*) &STATUS_REGISTER_BUFFER;


/*
 * Registers to store motion parameter data for the actuator
 */
unsigned char DATA_REGISTER_BUFFER[DATA_REGISTER_SIZE];

enum EASING_FUNCTION_TYPE {SIN=0, QAD=1, LIN=2, EXP=3, ELA=4, CIR=5, BOU=6, BAK=7, TRI=8, TRW=9, SNW=10, SPR=11};
enum EASING_CURVE_TYPE {IN=0, OU=1, IO=2};
typedef struct DATA_REGISTER_STRUCTURE
{
    unsigned int ANGLE:16;              //Relative address from base: 0
    unsigned int TIMING:16;             //Relative address from base: 2
    unsigned int DELAY:16;              //Relative address from base: 4
    
    unsigned int FREQUENCY:16;          //Relative address from base: 6
    unsigned int DAMPING:16;            //Relative address from base: 8
    unsigned int VELOCITY:16;           //Relative address from base: 10
    
    unsigned int EASING_FUNCTION:8;     //Relative address from base: 12
    unsigned int EASING_CURVE_TYPE:8;   //Relative address from base: 13

};

DATA_REGISTER_STRUCTURE *_DATA_REGISTERS = (struct DATA_REGISTER_STRUCTURE *) &DATA_REGISTER_BUFFER;


/*
 * Registers to store command data for the actuator
 */
unsigned char COMMAND_REGISTER_BUFFER[COMMAND_REGISTER_SIZE];

typedef struct COMMAND_REGISTER_STRUCTURE
{
    unsigned int ATTACH_PWM:8;              //Relative address from base: 0
    unsigned int DETACH_PWM:8;              //Relative address from base: 1
    unsigned int ATTACH_POWER:8;            //Relative address from base: 2
    unsigned int DETACH_POWER:8;            //Relative address from base: 3
    
    unsigned int TRIGGER:8;                 //Relative address from base: 4
    
    unsigned int CAL:8;                     //Relative address from base: 5

};

COMMAND_REGISTER_STRUCTURE *_COMMAND_REGISTERS = (struct COMMAND_REGISTER_STRUCTURE *) &COMMAND_REGISTER_BUFFER;


/*
 * variable to store current data register data
 */
uint8_t REG_ADDRESS = 0xFF;
uint8_t REQ_LENGTH = 0x00;
uint8_t REG_BLOCK_TYPE = INVALID_BLOCK;

/*
 * Function to convert register address to its respective Block type
 */
bool LoadAddressLength(uint8_t address, uint8_t _length)
{

  REG_BLOCK_TYPE = INVALID_BLOCK;
  
  if(address >= STATUS_REGISTER_BASE_ADDRESS && address < (STATUS_REGISTER_BASE_ADDRESS + STATUS_REGISTER_SIZE)){
    
    REG_BLOCK_TYPE = STATUS;
  }
  else
  if(address >= DATA_REGISTER_BASE_ADDRESS && address < (DATA_REGISTER_BASE_ADDRESS + DATA_REGISTER_SIZE)){
    
    REG_BLOCK_TYPE = DATA;
  }
  else
  if(address >= COMMAND_REGISTER_BASE_ADDRESS && address < (COMMAND_REGISTER_BASE_ADDRESS + COMMAND_REGISTER_SIZE)){
    
    REG_BLOCK_TYPE = COMMAND;
  }
  else
  if(address >= EEROM_REGISTER_BASE_ADDRESS && address < (EEROM_REGISTER_BASE_ADDRESS + EEROM_REGISTER_SIZE)){
    
    REG_BLOCK_TYPE = EEROM;
  }

  if(REG_BLOCK_TYPE != INVALID_BLOCK){
    REG_ADDRESS = address;
    REQ_LENGTH  = _length;
    return true;
  }
  
  return false;
}
