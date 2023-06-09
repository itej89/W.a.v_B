#include <Wire.h>
#include<SPI.h>


//byte WheelCommmandTemplate[17] = {0x00, 0x53, 0x53, 0xA9, 0x10, 0x10, 0x04, 0xFF, 0x53, 0x50, 0x00};


uint8_t BaseGSerialCopy[54];

#define SPI_BUFF_SIZE 34
uint8_t BaseGPacket[34];
int BaseGPacketIndex = 0;


enum SPIStates {RECIVE=0, PROCESS=1, SET_ACK = 2, SEND_ACK=3} SPITxRxState = RECIVE;
char SPIreceived;
bool SPIToBeProcessed = false;
ISR (SPI_STC_vect)                      
{
//  Serial.println("SPI!");
   if(SPITxRxState == RECIVE)
   {
     SPIreceived = SPDR;  
    //Serial.write(SPIreceived);
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






//4bytes - Kilometers, 2bytes Meters, 2bytes Millimeters, 1 byte Turn, 2 bytes Velocity
#define FL Address  0;
#define FRAddress  12;
#define RLAddress  12*2;
#define RRAddress  12*3;
#define YAW  12*4 
  //2 byte YAW value in (radians scalled by 1000). 
  //the 15 bit indicates sign (1 for negative, 0 for positive)
#define GY = 50 
  //2 byte GY value
  //Convert to radians/sec using double gzf = gy.z * (4000.0/65536.0) * (M_PI/180.0) * 25.0; 
  //the 15 bit indicates sign (1 for negative, 0 for positive)
#define ODO_DATA_LEN 20
#define X 52
#define Y  56
#define Vx  60
#define Vy  64
#define theta  68    //Yaw
#define oemga  70    //Angular velocity
#define ODOWrite  72 //Flag to see if new odo data available
byte I2cRegBank[(12*4)+2+2+4+4+4+4+2+2+1];
bool IsWireRequested = false;
byte BaseAddress = 0;
byte Datalen = 0;


//Protocol 1byte Address of regeister bank(Index), 1byte Data len, Data
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int Count) {
   while(2 > Wire.available());
  
       byte Address = Wire.read();
       byte len = Wire.read(); 
    
       if((Address & 0x80) != 0x00)
       {
        
         BaseAddress = (Address & 0x7F);
         
         Datalen = len;
         IsWireRequested = true;

       }
       else
       {
         while(len > Wire.available());
            
         for(int i=0; i<len; i++)
         {
            I2cRegBank[Address+i]  = Wire.read();
            
            
         }
       }
}

void requestEvent() {
  
  if(IsWireRequested)
  {
    IsWireRequested = false;
    Wire.write(&I2cRegBank[BaseAddress], Datalen);
  }
}



//void calibrate()
//{
//    //Standing backside of the robot
//    
//    for(int i=120; i< 180; i++)
//    {
//      WheelCommmandTemplate[4] = i; //FL
//      WheelCommmandTemplate[5] = i; //RL
//      WheelCommmandTemplate[6] = i; //FR
//      WheelCommmandTemplate[7] = i; //RR
//
//    Serial1.write(WheelCommmandTemplate, 17);
//    if(i==0) delay(3000);
//      delay(1000);
//
//      int highbyte = I2cRegBank[9];
//      int lowbyte  = I2cRegBank[8];
//        Serial.print(((highbyte<<8) | lowbyte));  //FL
//        Serial.print(", ");
//     highbyte = I2cRegBank[21];
//     lowbyte  = I2cRegBank[20];
//        Serial.print(((highbyte<<8) | lowbyte));  //FR
//        Serial.print(", ");
//     highbyte = I2cRegBank[33];
//     lowbyte  = I2cRegBank[32];
//        Serial.print(((highbyte<<8) | lowbyte));  //RL
//        Serial.print(", ");
//     highbyte = I2cRegBank[45];
//     lowbyte  = I2cRegBank[44];
//        Serial.println(((highbyte<<8) | lowbyte));//RR
//    }
//}


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Wire.begin(10);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); 

  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 
  SPCR |= _BV(SPE);    
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
}



void loop() {

  while (Serial.available()) {      // If anything comes in Serial (USB),

    byte ch = Serial.read();
    Serial1.write(ch);   // read it and send it out Serial1 (pins 0 & 1)

}

  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
      BaseGSerialCopy[49] = Serial1.read(); 
//      Serial.write(BaseGSerialCopy[49]);
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
            memcpy(&I2cRegBank[48], &BaseGPacket[26], sizeof(BaseGPacket[0])*2);
            memcpy(&I2cRegBank[50], &BaseGPacket[28], sizeof(BaseGPacket[0])*2);
            
            memcpy(BaseGSerialCopy, &BaseGPacket[2], sizeof(BaseGPacket[0])*28);
            BaseGSerialCopy[50] = 0x00;
            BaseGSerialCopy[51]++;
            if(I2cRegBank[ODOWrite] == 1)
            {              
              memcpy(&BaseGSerialCopy[28], &I2cRegBank[52], sizeof(BaseGPacket[0])*21);
              I2cRegBank[ODOWrite] = 0;  
            }
            else
            {
              BaseGSerialCopy[48] = 0x00;
            }
            memcpy(&BaseGSerialCopy[52], &BaseGPacket[32], sizeof(BaseGPacket[0])*2);
            Serial.write(BaseGSerialCopy, 54);
          
            if(BaseGSerialCopy[49] != 0x00)
            {
              BaseGSerialCopy[49] = 0x00;
            }
            

//                  long DX = BaseGSerialCopy[28];
//                    DX = DX << 8 | BaseGSerialCopy[29];
//                    DX = DX << 8 | BaseGSerialCopy[30];
//                    DX = DX << 8 | BaseGSerialCopy[31];
//                    Serial.print("X : ");
//                    Serial.println(DX, DEC);
                    
//            Serial.print(BaseGSerialCopy[0], HEX);
//            Serial.print(" ");
//            Serial.print(BaseGSerialCopy[1], HEX);
//            Serial.print(" ");
//            Serial.print(BaseGSerialCopy[50], HEX);
//            Serial.print(" ");
//            Serial.print(BaseGSerialCopy[51], HEX);
//            Serial.print(" ");
//            Serial.print(BaseGSerialCopy[52], HEX);
//            Serial.println("");
           
            
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
//  
//  if(BaseGSerialCopy[49] != 0x00)
//  {
//     Serial.write(BaseGSerialCopy, 54);  
//     BaseGSerialCopy[49] = 0x00;
//  }

  delayMicroseconds(10);

}




















//Print ODO MEasurements
//
//                    long DX = I2cRegBank[52];
//                    DX = DX << 8 | I2cRegBank[53];
//                    DX = DX << 8 | I2cRegBank[54];
//                    DX = DX << 8 | I2cRegBank[55];
//                    Serial.print("X : ");
//                    Serial.println(DX, HEX);

//                    long DY = I2cRegBank[56];
//                    DY = DY << 8 | I2cRegBank[57];
//                    DY = DY << 8 | I2cRegBank[58];
//                    DY = DY << 8 | I2cRegBank[59];
//
//                    
//                    long V_LinearX = I2cRegBank[60];
//                    V_LinearX = V_LinearX << 8 | I2cRegBank[61];
//                    V_LinearX = V_LinearX << 8 | I2cRegBank[62];
//                    V_LinearX = V_LinearX << 8 | I2cRegBank[63];
//
//                    
//                    long V_LinearY = I2cRegBank[64];
//                    V_LinearY = V_LinearY << 8 | I2cRegBank[65];
//                    V_LinearY = V_LinearY << 8 | I2cRegBank[66];
//                    V_LinearY = V_LinearY << 8 | I2cRegBank[67];
//                    
//                    uint16_t YawInfo = ((I2cRegBank[68]<<8) | I2cRegBank[69]);
//                    uint16_t AngVelInfo = ((I2cRegBank[70]<<8) | I2cRegBank[71]);
//                    
//           
//                    Serial.print("Y : ");
//                    Serial.println(DY, HEX);
//                    Serial.print("I2cRegBank[60] : ");
//                    Serial.println(I2cRegBank[60], HEX);
//                    Serial.print("I2cRegBank[61] : ");
//                    Serial.println(I2cRegBank[61], HEX);
//                    Serial.print("I2cRegBank[62] : ");
//                    Serial.println(I2cRegBank[62], HEX);
//                    Serial.print("I2cRegBank[63] : ");
//                    Serial.println(I2cRegBank[63], HEX);
//                    Serial.print("V_LinearX : ");
//                    Serial.println(V_LinearX, HEX);
//                    Serial.print("V_LinearY : ");
//                    Serial.println(V_LinearY, HEX);
//                    Serial.print("YawInfo : ");
//                    Serial.println(YawInfo, HEX);
//                    Serial.print("AngVelInfo : ");
//                    Serial.println(AngVelInfo, HEX);




            //double gzf = ((I2cRegBank[50]<<8) | I2cRegBank[51]) * (4000.0/65536.0) * (M_PI/180.0) * 25.0;
           // Serial.println(((I2cRegBank[50]<<8) | I2cRegBank[51]), DEC);
