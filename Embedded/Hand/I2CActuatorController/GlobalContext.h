#pragma once

#include "Registers.h"

/*
  Buffer to store a copy of Data register 
  while performing actual servo motion
*/
unsigned char DATA_REGISTER_BUFFER_WORKING_COPY[DATA_REGISTER_SIZE];
void clone_data_registers(){
  memcpy(DATA_REGISTER_BUFFER_WORKING_COPY, DATA_REGISTER_BUFFER, DATA_REGISTER_SIZE);
}
DATA_REGISTER_STRUCTURE *DATA_REGISTERS_WORKING_COPY = (struct DATA_REGISTER_STRUCTURE *) &DATA_REGISTER_BUFFER_WORKING_COPY;


bool is_data_register_new()
{
    if(DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION == SNW ||
            DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION == TRW ||
            DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION == SPR)
    return true;
    
    else if( DATA_REGISTERS_WORKING_COPY->ANGLE              == _DATA_REGISTERS->ANGLE && 
        DATA_REGISTERS_WORKING_COPY->TIMING             == _DATA_REGISTERS->TIMING &&
        DATA_REGISTERS_WORKING_COPY->DELAY              == _DATA_REGISTERS->DELAY &&
        
        DATA_REGISTERS_WORKING_COPY->FREQUENCY          == _DATA_REGISTERS->FREQUENCY &&
        DATA_REGISTERS_WORKING_COPY->DAMPING            == _DATA_REGISTERS->DAMPING &&
        DATA_REGISTERS_WORKING_COPY->VELOCITY           == _DATA_REGISTERS->VELOCITY &&
        
        DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION    == _DATA_REGISTERS->EASING_FUNCTION &&
        DATA_REGISTERS_WORKING_COPY->EASING_CURVE_TYPE  == _DATA_REGISTERS->EASING_CURVE_TYPE
    )
    return false;
    
    else return true;
}




/*
  Servo object
*/
Servo servo_motor; 


/*
  Variable to count the number of 
  Trigger requests received on I2C
*/
uint8_t TRIGGER_REQUEST_COUNT = 0;
