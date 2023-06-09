#pragma once

void DEBUG_PRINT_STRING(char* message){
  #ifdef ENABLE_DEBUG_MESSAGES
  Serial.println(message);
  #endif
}

void DEBUG_PRINT_VALUE(long value){
  #ifdef ENABLE_DEBUG_MESSAGES
  Serial.print(value);
  #endif
}

void DEBUG_PRINT_HEX_VALUE(long value){
  #ifdef ENABLE_DEBUG_MESSAGES
  Serial.print(value, HEX);
  #endif
}
