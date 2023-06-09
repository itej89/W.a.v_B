#include <rgb_lcd.h>

#include <Wire.h>
#include<SPI.h>


rgb_lcd lcd;


uint8_t HeadStraight[10] = {0x00, 0x53, 0x53, 0x86, 0xD3, 0x84, 0xD3, 0x53, 0x50, 0x00};


uint8_t BaseGSerialCopy[29];

#define SPI_BUFF_SIZE 34
uint8_t BaseGPacket[34];
int BaseGPacketIndex = 0;



enum SPIStates {RECIVE=0, PROCESS=1, SET_ACK = 2, SEND_ACK=3} SPITxRxState = RECIVE;
char SPIreceived;
bool SPIToBeProcessed = false;
ISR (SPI_STC_vect)                      
{
  
   if(SPITxRxState == RECIVE)
   {
     SPIreceived = SPDR;  
     
     SPIToBeProcessed = true;
     SPITxRxState = SET_ACK;
   }
   else if(SPITxRxState == SET_ACK)
   {
      char shift = SPDR;
      if(SPIToBeProcessed == false)
      {
        byte shiftplusOne = (shift+1);
        SPDR = shiftplusOne;

    
        SPITxRxState = SEND_ACK;
      }
   }
   else if(SPITxRxState == SEND_ACK)
   {
      char shift = SPDR;
      SPITxRxState = RECIVE;
   }
}






#define HSR_ACK  24;



void setup() {

    lcd.begin(16, 2);
    
    lcd.setRGB(255, 255, 255);
    
    // Print a message to the LCD.
    lcd.print("W.a.v B!");



  Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 
  SPCR |= _BV(SPE);    
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation

  Serial1.write(HeadStraight, 10);
  long  lastsent = millis();
  while(Serial1.available() <= 0 && abs(millis() - lastsent) < 5000 );
  
  Serial1.read();
  
  
}



void loop() {
  while (Serial.available()) {      // If anything comes in Serial (USB),
    byte ch = Serial.read();
    Serial1.write(ch);   // read it and send it out Serial1 (pins 0 & 1)
    BaseGSerialCopy[24] = 0x00;
}

  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
   // Serial.write(S);   // read it and send it out Serial (USB)
   
    Serial1.read();
   BaseGSerialCopy[24] = Serial1.read();
  }



   if(SPITxRxState == SET_ACK && SPIToBeProcessed)
  {
    if(BaseGPacketIndex > 1)
    {
      if(BaseGPacket[0] == 'B' && BaseGPacket[1] == 'G')
      {
          BaseGPacket[BaseGPacketIndex++] = SPIreceived;
        
          if(BaseGPacketIndex >= SPI_BUFF_SIZE)
          {
             
            memcpy(BaseGSerialCopy, &BaseGPacket[2], sizeof(BaseGPacket[0])*24);

            
            
            memcpy(&BaseGSerialCopy[25], &BaseGPacket[30], sizeof(BaseGPacket[0])*4);
            Serial.write(BaseGSerialCopy, 29);
            BaseGPacketIndex = 0;
          }
      }
      else
      {
        BaseGPacketIndex = 2;
        BaseGPacket[0] = BaseGPacket[1];
        BaseGPacket[1] = SPIreceived;
      }
    }
    else
    { 
      BaseGPacket[BaseGPacketIndex++] = SPIreceived;
      
    }
    
    SPIToBeProcessed = false;
  }

  delayMicroseconds(10);

}
