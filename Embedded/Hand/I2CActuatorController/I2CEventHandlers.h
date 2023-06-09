#pragma once

#include "GlobalConfiguration.h"
#include "Registers.h"
#include "CommandHandler.h"

void requestEvent(){
 
          DEBUG_PRINT_STRING("Requested recieve.");
    switch(REG_BLOCK_TYPE){

      
        
        case EEROM:{
          DEBUG_PRINT_STRING("Requested EEPROM.");
          while(REQ_LENGTH > 0){
            Wire.write(EEPROM.read(REG_ADDRESS - EEROM_REGISTER_BASE_ADDRESS));
            REG_ADDRESS ++;
            REQ_LENGTH --;
            }

            REG_BLOCK_TYPE = INVALID_BLOCK;
            
          break;
          }
 
        case STATUS:{
          DEBUG_PRINT_STRING("Requested Status.");
          while(REQ_LENGTH > 0){
            Wire.write(STATUS_REGISTER_BUFFER[REG_ADDRESS - STATUS_REGISTER_BASE_ADDRESS]);
            REG_ADDRESS ++;
            REQ_LENGTH --;
            }

            REG_BLOCK_TYPE = INVALID_BLOCK;
            
          break;
        }
    }
}


long start_of_transmission = millis();
void receiveEvent(int count){


//          DEBUG_PRINT_STRING("Recivce event");
  
  long end_of_last_transmission = millis();
  while(Wire.available()<2 || millis()-start_of_transmission < MAX_I2C_COMMAND_BYTE_TRANSMISSION_TIME_MS){
      delay(1);  
  }
    
  //Wait until a minimum of two bytes available on the bus
  if(Wire.available() >= 2)
  {
      /*
       * Condition to detect start of new command transmission
       * No current valid block under transmission or last transmission exceeded maximum transmission time
       */
      if(REG_BLOCK_TYPE == INVALID_BLOCK || millis()-end_of_last_transmission > MAX_I2C_COMMAND_TRANSMISSION_TIME_MS){
        uint8_t _address = Wire.read();
        uint8_t _length = Wire.read(); 
          DEBUG_PRINT_STRING("Loaded values");
        
        if(!LoadAddressLength(_address, _length)) return;
      }
  }
  else
  {
    while(Wire.available()){Wire.read();}
  }
      
      
      switch(REG_BLOCK_TYPE){
        case DATA:{


          DEBUG_PRINT_STRING("Received Data.");
          /*
           * Loop untill requested length is completely recieved
           */
              DEBUG_PRINT_STRING("Data recieved : ");
          while(Wire.available() > 0 && REQ_LENGTH > 0){
              DATA_REGISTER_BUFFER[REG_ADDRESS - DATA_REGISTER_BASE_ADDRESS] = Wire.read();
              DEBUG_PRINT_HEX_VALUE(DATA_REGISTER_BUFFER[REG_ADDRESS - DATA_REGISTER_BASE_ADDRESS]);
              REG_ADDRESS ++;
              REQ_LENGTH --;
  
              end_of_last_transmission = millis();
            }

            if(REQ_LENGTH == 0){
              REG_BLOCK_TYPE = INVALID_BLOCK;
            }
            
          break;
        }
        case COMMAND:{
          
          DEBUG_PRINT_STRING("Received Command.");
          /*
           * Loop untill requested length is completely recieved
           */
          while(REQ_LENGTH > 0){
              DEBUG_PRINT_STRING("Commadn Address : ");
              DEBUG_PRINT_VALUE(REG_ADDRESS - COMMAND_REGISTER_BASE_ADDRESS);
              COMMAND_REGISTER_BUFFER[REG_ADDRESS - COMMAND_REGISTER_BASE_ADDRESS] = SET;
              REG_ADDRESS ++;
              REQ_LENGTH --;
              end_of_last_transmission = millis();
            }

            if(REQ_LENGTH == 0){
              REG_BLOCK_TYPE = INVALID_BLOCK;
              serve_command();
            }
            
          break;
        }
        case STATUS:{
          
          DEBUG_PRINT_STRING("Received Status.");
        }
      }

}
