
#include <Wire.h>

#define I2C_ADDRESS 5
#define COMMAND_READ_TIMEOUT 5000

void i2cReceiveEvent(int count){

  Serial.print("Recieved Event : ");
  Serial.println(count);
  if(Wire.available())
  {
    uint8_t inByte = Wire.read();
    Serial.println(inByte, HEX);

  }
}

void SerialRecieved(){
  // Wait for incoming data
  if (Serial.available() > 1)
  {

    //Read length of the data
    int frameLength = Serial.read();
    int i2cAddress = Serial.read();
    

    //Wait till complete information has been recieved


    
    int Timeout = 0;
    int byteIdx = 0;
    int dataLength = 0;
    Wire.beginTransmission((i2cAddress & 0x7F));

    
    while(byteIdx < frameLength && Timeout < COMMAND_READ_TIMEOUT){

      //Keep reading data from serial and write it to I2C
      while(Serial.available() > 0){

        //Readn and Transmit data
        uint8_t inByte = Serial.read();
        Wire.write(inByte);

        if(byteIdx == 1){
          dataLength = inByte;
        }

        
        byteIdx ++;
        Timeout = 0;
      }

      delay(1);
      Timeout++;
    }

    
    Wire.endTransmission();
    



    //Recive data if read mode is requested
    if((i2cAddress & 0x80) == 0x80){

      int Timeout = 0;
      int byteIdx = 0;
//      Serial.println(dataLength, HEX);
      Wire.requestFrom(i2cAddress, dataLength);
      do
      {
          uint8_t inByte = Wire.read();
          Serial.write(inByte);
          byteIdx++;
        
      }
      while(byteIdx < dataLength && Timeout < COMMAND_READ_TIMEOUT);
    }
    else{
    Serial.write(96);
    }
    

    
    
  }

}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);


  Wire.begin(I2C_ADDRESS);                
  TWAR = (I2C_ADDRESS<<1)|1;
  Wire.onReceive(i2cReceiveEvent); 
}

void loop() {

  SerialRecieved();
  delay(1);
  
}
