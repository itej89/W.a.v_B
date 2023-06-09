
#include <Wire.h>
#include <PID_v1.h>
#include<math.h>

#define MAKEBYTE_16BIT(X,H,L) {\
if (H != 0x7F)\
{\
  X=H;\
  X = X<<8;\
}\
X |= L;\
}   



long LastControlRecieved = micros();

uint16_t FRMotorDelay = 0x23FF;
uint16_t FLMotorDelay = 0x23FF;
uint16_t RRMotorDelay = 0x23FF;
uint16_t RLMotorDelay = 0x23FF;

uint16_t LinearSpeed = 0x00;
uint16_t AngularSpeed = 0x00;

               //RL-FL-FR-RR //PF0-PF7
//uint8_t RegMotorDirection = 0b10010101;

#define MV_NOP_REG  0x00
#define MV_FORWARD_X_REG  0x6A
#define MV_BAKWARD_X_REG  0x95
#define MV_LEFT_Y_REG  0xA6
#define MV_RIGHT_Y_REG 0x59
#define MV_TURN_Z_CLOCKWISE_REG  0x9A
#define MV_TURN_Z_ANTI_CLOCKWISE_REG  0x65


#define MV_DIR_PORT PORTF

#define PWM_FL 4  //PE4
#define PWM_FR 3  //PE3
#define PWM_RL 13 //PB5
#define PWM_RR 14 //PB6

bool PWM_ON = false;

#define MDIR_STOP         0xFF
#define MDIR_MOVE_UP      0x01
#define MDIR_MOVE_DOWN    0x02
#define MDIR_MOVE_RIGHT   0x03
#define MDIR_MOVE_LEFT    0x04
#define MDIR_STEER_Q1     0x11
#define MDIR_STEER_Q2     0x12
#define MDIR_STEER_Q3     0x13
#define MDIR_STEER_Q4     0x14
#define MDIR_SLIDE_Q1     0x21
#define MDIR_SLIDE_Q2     0x22
#define MDIR_SLIDE_Q3     0x23
#define MDIR_SLIDE_Q4     0x24
#define MDIR_TURN_CLOCKWISE      0x31
#define MDIR_TURN_ANTICLOCKWISE  0x32
#define MDIR_AKR_STEER_Q1      0x33
#define MDIR_AKR_STEER_Q2      0x34
#define MDIR_AKR_STEER_Q3      0x35
#define MDIR_AKR_STEER_Q4      0x36

//0Byte Motion Direction
//0b 00 00 00 00 --> 
  //00 STOP
  //01 : MOVE_UP, 02 : MOVE_DOWN, 03 : MOVE_RIGHT, 04 : MOVE_LEFT
  //11 : STEER_Q1, 12 : STEER_Q2, 13 : STEER_Q3, 14 : STEER_Q4
  //21 : SLIDE_Q1, 22 : SLIDE_Q2, 23 : SLIDE_Q3, 24 : SLIDE_Q4
  //31 : TURN_CLOCKWISE, 32 : TURN_ANTICLOCKWISE

//FL    RL   FR   RR
//[8,7][6,5][4,3][2,1]Bytes RequiredSpeed in mm/sec FL RL FR RR
//[16,15][14,13][12,11][10,9]PWM Bytes FL RL FR RR
byte I2cRegBank[25] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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




/* Configure digital pins 9 and 10 as 16-bit PWM outputs. */
void setupPWM16() {
    DDRB |= _BV(PB5) | _BV(PB6);        /* set pins as outputs */
    TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
    TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS11);                    /* div 8 prescaling to remove hum at lower duty cycle */
    ICR1 = 0xffff;                      /* TOP counter value */



      DDRE |= _BV(PE3) | _BV(PE4);        /* set pins as outputs */
    TCCR3A = _BV(COM3A1) | _BV(COM3B1)  /* non-inverting PWM */
        | _BV(WGM31);                   /* mode 14: fast PWM, TOP=ICR1 */
    TCCR3B = _BV(WGM33) | _BV(WGM32)
        | _BV(CS31);                    /* div 8 prescaling to remove hum at lower duty cycle */
    ICR3 = 0xffff; 

    PWM_ON = true;
}

void StopPWM()
{
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  
  TCCR3A = 0x00;
  TCCR3B = 0x00;
  
  PWM_ON = false;
}

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val)
{
    if(val == 0)
    {
      pinMode(pin, LOW);  
    }
    else
    {
      switch (pin) {
          case  13: OCR1A = val; break;
          case  14: OCR1B = val; break;
          case   3: OCR3A = val; break;
          case   4: OCR3B = val; break;
      }
    }
}


void setup() {
    DDRF = 0xFF;
    pinMode(PWM_RL, OUTPUT);
    pinMode(PWM_RR, OUTPUT);
    pinMode(PWM_FR, OUTPUT);
    pinMode(PWM_FL, OUTPUT);

    Serial.begin(115200);
    Serial1.begin(115200);
    PORTF = 0x00;
    
    Wire.begin(11);                
    Wire.onReceive(receiveEvent); 
    Wire.onRequest(requestEvent); 
}

void StopMotion()
{
//      Serial.write(0xDD);
     

      I2cRegBank[0] = MDIR_STOP;
      //Set Requested Velocity to Zero
      //FL RL FR RR
      I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = 0;
      I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = 0;

      I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = 0;
      I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = 0;

      I2cRegBank[17] = I2cRegBank[19] = I2cRegBank[21] = I2cRegBank[23] = 0;
      I2cRegBank[18] = I2cRegBank[20] = I2cRegBank[22] = I2cRegBank[24] = 0;

//      //Make PWM Zero
//      while(RLMotorDelay > 2000 || FRMotorDelay > 2000 || RRMotorDelay > 2000 || FLMotorDelay > 2000)
//      {
//        if(RLMotorDelay > 2000){RLMotorDelay = RLMotorDelay/2; analogWrite16(PWM_RL,RLMotorDelay);}
//        if(FRMotorDelay > 2000){FRMotorDelay = FRMotorDelay/2; analogWrite16(PWM_FR,FRMotorDelay);}
//        if(RRMotorDelay > 2000){RRMotorDelay = RRMotorDelay/2; analogWrite16(PWM_RR,RRMotorDelay);}
//        if(FLMotorDelay > 2000){FLMotorDelay = FLMotorDelay/2; analogWrite16(PWM_FL,FLMotorDelay);}
//        delay(10);
//      }
//        
      analogWrite16(PWM_RL,0);
      analogWrite16(PWM_FR,0);
      analogWrite16(PWM_RR,0);
      analogWrite16(PWM_FL,0);  

       //HOLD DC Drivers
      MV_DIR_PORT = MV_NOP_REG;
      
      //Stop PWM Timer
      if(PWM_ON == true)
      {
        StopPWM();
      }

      delay(1500);
}

bool IsControlling = false;
void CheckSerial();
void loop() {
  delay(10);


    if(MV_DIR_PORT != MV_NOP_REG && (micros() > LastControlRecieved) && (abs(micros() - LastControlRecieved)/1000 < 50))
    {
          IsControlling = true;
          
//        Serial.println("Controlling");
          FLMotorDelay = ((I2cRegBank[9] << 8) | I2cRegBank[10]);
          RLMotorDelay = ((I2cRegBank[11] << 8) | I2cRegBank[12]);
          FRMotorDelay = ((I2cRegBank[13] << 8) | I2cRegBank[14]);
          RRMotorDelay = ((I2cRegBank[15] << 8) | I2cRegBank[16]);
          
        if(FLMotorDelay != 0 || RLMotorDelay != 0 || FRMotorDelay != 0 || RRMotorDelay != 0)
        {    
          analogWrite16(PWM_RL,RLMotorDelay);
          analogWrite16(PWM_FR,FRMotorDelay);
          analogWrite16(PWM_RR,RRMotorDelay);
          analogWrite16(PWM_FL,FLMotorDelay);
        }
    }
    else
    if(MV_DIR_PORT != MV_NOP_REG && (micros() > LastControlRecieved) && abs(micros() - LastControlRecieved)/1000 < 500)
    {
      if(MV_DIR_PORT != MV_NOP_REG && IsControlling)
      {
//        Serial.println("Controlling Timeout");
        IsControlling = false;
      }
    } 
    else
    if(MV_DIR_PORT != MV_NOP_REG)
    {
      StopMotion(); 
    }

    if(!IsControlling)
    {
      CheckSerial();  
    }
}


int ExtractDirection(uint16_t ServoInfo)
{
  
      switch((ServoInfo >> 15))
      {
        case 0:
        return -1;
        case 1:
        return 1;
      }
}

double ExtractAngularVelocity(uint16_t VelocityInfo)
{
  uint16_t velocity_scaled = (VelocityInfo & 0x7FFF);
  double velocity = velocity_scaled/10000.0;
 
//        Serial.print("ang velocity_scaled : ");
//        Serial.println(velocity_scaled, HEX);
//
//        
//        Serial.print("ang velocity : ");
//        Serial.println(velocity, DEC);
   return velocity;
}



double ExtractLinearVelocity(uint16_t VelocityInfo)
{
   return (VelocityInfo & 0x7FFF);
}

uint16_t EstimatePWMFromVelocity(double Velocity)
{
    //LEAST PWM = 16 FF(5887) -->  10 mm/sec
    //HIGHEST PWM = 59FF(23039) --> 320mm/sec
    //
    //per 1mm --> Raise in PWM = 55.32
    //
    //For Kmm/sec => PWM = 5887+(55.32  *K)
   return 5887+(55.32  *Velocity);
}


uint16_t GetTurnInfo(int Direction, uint16_t RadiansScaled)
{
    return ((Direction << 14) | RadiansScaled);
}





//byte WheelCommmandTemplate[17] = {0x00, 0x53, 0x53, 0xA9, 0x10, 0x10, 0x04, 0xFF, 0x53, 0x50, 0x00};

byte ServoControl[14] = {0x00, 0x53, 0x53, 

                              //*****************************************************************************/
                              //Delta TurnAngles in (radians*10000)...max radians is 2^14
                                        //These values need to be divided by 10000 for turning angle in radians
                                        
                              //The Highest two bits represents the sign of the Turn
                                        //bit 15,14 == 10 means RightTurn, 01 means left turn,
                                        //             11 means Zero Turn, 00 means Disconnect Servo

                                        
                              //Looking standing behind the robot the order of the bytes is below
                                      //[3,4]:FL   [5,6]:FL    [7,8]:FL    [9,10]:FL
                              //********************************************************/
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                              //*****************************************************************************/

                                0x53, 0x50, 0x00};

bool sendServo(bool Should_Wait)
{ 

  while(Serial1.available())
  {
    Serial1.read();
  }
  
  Serial1.write(ServoControl,14);
  long lastReadTime = micros();

  if(!Should_Wait) return true;
  
  bool ack_recieved = false;
  
  while(Serial1.available() <= 0)
  {
    if(micros() < lastReadTime || (abs(micros() - lastReadTime)/1000) > 5000)
    {return false;}
  }
  

  bool ack_ready = false;
  int count = Serial1.available();
  for(int i=0; i<count; i++)
  {
    if(Serial1.read() == 0xBB)
    {
        lastReadTime = micros();
        ack_ready = true;
        break;
    }
  }

  if(ack_ready)
  {

     while(Serial1.available() <= 0)
      {
        if(micros() < lastReadTime || (abs(micros() - lastReadTime)/1000) > 5000)
        {return false;}
      }
      
      int count = Serial1.available();
      for(int i=0; i<count; i++)
      {
        if(Serial1.read() == 0xCC)
        {
            ack_recieved = true;
        }
      }
  }

  return ack_recieved;
}

bool turnServo(uint8_t next_state)
{
    bool Should_Wait = false;
    if(MV_DIR_PORT == MDIR_TURN_CLOCKWISE || MV_DIR_PORT == MDIR_TURN_ANTICLOCKWISE)
    {
      if(next_state == MDIR_TURN_CLOCKWISE || next_state == MDIR_TURN_ANTICLOCKWISE)
      {
          //No operation  
      }
      else
      {
         //Stop the motors
         StopMotion();
         Should_Wait  = true;
         sendServo(Should_Wait);
      }
    }
      if(next_state == MDIR_TURN_CLOCKWISE || next_state == MDIR_TURN_ANTICLOCKWISE)
      {
        //Stop the motors
        StopMotion();
        Should_Wait  = true;
        sendServo(Should_Wait);
      }
      else
      {
         sendServo(Should_Wait);
      } 
    

  return true;
  
}

int index = 0;
byte c[10];
void CheckSerial() {

  if(Serial.available() <= 0)
  {
      Serial.write(0xCC);
      return;  
  }
  while (Serial.available()) {
    //if(Serial.available())
    //{
      byte inChar = (byte)Serial.read();
    
     
      if(inChar != '\0')
      {
//     Serial.print(index);
//     Serial.print(" : ");
//     Serial.println(inChar,HEX);
        c[index++] = inChar;
      }
      else
      if(index > 1 && c[0] == 'S' && (c[1] == 'S' || c[1] == 'T'))
      {
//     Serial.print(index);
//     Serial.print(" : ");
//     Serial.println(inChar,HEX);
         c[index++] = inChar;
      }
      else
        index = 0;

     
    //}
    
  if(index == 8 && (c[0] == 'S' && c[1] == 'T' && c[6] == 'S' && c[7] == 'P'))
  { 
    index = 0;
    LastControlRecieved = micros();
    //Highest bit indicates sign of the rotation
    //1 for positive(Forward) and 0 for negative(BackWard)
    uint16_t LinearXInfo  = ((c[2] << 8) | c[3]);
    //1 for positive(right turn) and 0 for negative(left turn)
    uint16_t AngularDegreeInfo = ((c[4] << 8) | c[5]);


    int LinearXDirection = ExtractDirection(LinearXInfo);
    int AngularDirection = ExtractDirection(AngularDegreeInfo);
    
    double LinearXVelocity = ExtractLinearVelocity(LinearXInfo); //in mm/sec
    
    //used same scalling for Angular velocity and Angular degree information
    double AngularDegree = ExtractAngularVelocity(AngularDegreeInfo); //in rad
    double AngularDegreeScaled = AngularDegree * 10000;
    
    //Set Requested Velocity LinearXVelocity
    //FL                RL              FR              RR
    I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = (((int)LinearXVelocity >> 8) & 0xFF);
    I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = (((int)LinearXVelocity) & 0xFF);


    uint16_t PWM = EstimatePWMFromVelocity(LinearXVelocity);
    
    //Set Initial Speed PWM values, Will be modified by Ododmeter
    //FL                  RL                FR              RR
    I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = ((PWM >> 8) & 0xFF);
    I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = ((PWM) & 0xFF);


    //Set Initial Speed PWM values, will be updated from I2cRegBank
    RLMotorDelay = PWM;
    FLMotorDelay = PWM;
    RRMotorDelay = PWM;
    FRMotorDelay = PWM;

        if(AngularDegree == 0)
        {
          
            //Current Servo delta angles
            //FL                  RL                FR              RR
            I2cRegBank[17] = I2cRegBank[19] = I2cRegBank[21] = I2cRegBank[23] = 0xC0;
            I2cRegBank[18] = I2cRegBank[20] = I2cRegBank[22] = I2cRegBank[24] = 0x00;
          
            ServoControl[3] = ServoControl[5] = ServoControl[7] = ServoControl[9] = 0xC0;
            ServoControl[4] = ServoControl[6] = ServoControl[8] = ServoControl[10] = 0x00;
          
          
            if(LinearXDirection == 1 && 
              turnServo(MV_FORWARD_X_REG))
            {
              MV_DIR_PORT = MV_FORWARD_X_REG;
              I2cRegBank[0]  = MDIR_MOVE_UP;
            }
            else
            if(LinearXDirection == -1 && 
              turnServo(MV_BAKWARD_X_REG))
            {
              MV_DIR_PORT = MV_BAKWARD_X_REG;
              I2cRegBank[0]  = MDIR_MOVE_DOWN;
            }
            
        }
        else
         //Make Right Turn
        if(AngularDirection == -1)
        {
          if(LinearXDirection == 1)
          {
            uint16_t FR_TurnInfo;
            uint16_t FL_TurnInfo;
            
            //Front Wheels steered in Left direction
            FR_TurnInfo = GetTurnInfo(1,AngularDegreeScaled);
            FL_TurnInfo = GetTurnInfo(1,AngularDegreeScaled);

            I2cRegBank[17] = ServoControl[3] = ((FL_TurnInfo >> 8) & 0xFF);
            I2cRegBank[18] = ServoControl[4] = (FL_TurnInfo & 0xFF);
            
            I2cRegBank[21] = ServoControl[7] = ((FR_TurnInfo >> 8) & 0xFF);
            I2cRegBank[22] = ServoControl[8] = (FR_TurnInfo & 0xFF);

            //Steer Back wheels straight while going farward
            //RL                  RR
            I2cRegBank[19] = I2cRegBank[23] = 0xC0;
            I2cRegBank[20] = I2cRegBank[24] = 0x00;
            
            ServoControl[5] = ServoControl[9] =  0xC0;
            ServoControl[6] = ServoControl[10] = 0x00;

            if(turnServo(MV_FORWARD_X_REG))
            {
                MV_DIR_PORT = MV_FORWARD_X_REG;
                I2cRegBank[0]  = MDIR_AKR_STEER_Q2;
            }
          
          }
          else
          if(LinearXDirection == -1)
          {
            uint16_t RR_TurnInfo;
            uint16_t RL_TurnInfo;
            
            //Front Wheels steered in Left direction
            RR_TurnInfo = GetTurnInfo(2,AngularDegreeScaled);
            RL_TurnInfo = GetTurnInfo(2,AngularDegreeScaled);

            I2cRegBank[19] = ServoControl[5] = ((RL_TurnInfo >> 8) & 0xFF);
            I2cRegBank[20] = ServoControl[6] = (RL_TurnInfo & 0xFF);
            
            I2cRegBank[23] = ServoControl[9] = ((RR_TurnInfo >> 8) & 0xFF);
            I2cRegBank[24] = ServoControl[10] = (RR_TurnInfo & 0xFF);

            //Steer Front wheels straight while going backward
            //FL                  FR
            I2cRegBank[17] = I2cRegBank[21] = 0xC0;
            I2cRegBank[18] = I2cRegBank[22] = 0x00;
            
            ServoControl[3] = ServoControl[7] =  0xC0;
            ServoControl[4] = ServoControl[8] = 0x00;

            if(turnServo(MV_BAKWARD_X_REG))
            {
                MV_DIR_PORT = MV_BAKWARD_X_REG;
                I2cRegBank[0]  = MDIR_AKR_STEER_Q4;
            }
          }
        }
        else
         //Make Left Turn
        if(AngularDirection == 1)
        {
          if(LinearXDirection == 1)
          {
            uint16_t FR_TurnInfo;
            uint16_t FL_TurnInfo;
            
            //Front Wheels steered in Left direction
            FR_TurnInfo = GetTurnInfo(2,AngularDegreeScaled);
            FL_TurnInfo = GetTurnInfo(2,AngularDegreeScaled);

            I2cRegBank[17] = ServoControl[3] = ((FL_TurnInfo >> 8) & 0xFF);
            I2cRegBank[18] = ServoControl[4] = (FL_TurnInfo & 0xFF);
            
            I2cRegBank[21] = ServoControl[7] = ((FR_TurnInfo >> 8) & 0xFF);
            I2cRegBank[22] = ServoControl[8] = (FR_TurnInfo & 0xFF);

            //Steer Back wheels straight while going farward
            //RL                  RR
            I2cRegBank[19] = I2cRegBank[23] = 0xC0;
            I2cRegBank[20] = I2cRegBank[24] = 0x00;
            
            ServoControl[5] = ServoControl[9] =  0xC0;
            ServoControl[6] = ServoControl[10] = 0x00;

            
            if(turnServo(MV_FORWARD_X_REG))
            {
                MV_DIR_PORT = MV_FORWARD_X_REG;
                I2cRegBank[0]  = MDIR_AKR_STEER_Q2;
            }
          }
          else
          if(LinearXDirection == -1)
          {
            
            uint16_t RR_TurnInfo;
            uint16_t RL_TurnInfo;
            
            //Front Wheels steered in Left direction
            RR_TurnInfo = GetTurnInfo(1,AngularDegreeScaled);
            RL_TurnInfo = GetTurnInfo(1,AngularDegreeScaled);
  
            I2cRegBank[19] = ServoControl[5] = ((RL_TurnInfo >> 8) & 0xFF);
            I2cRegBank[20] = ServoControl[6] = (RL_TurnInfo & 0xFF);
            
            I2cRegBank[23] = ServoControl[9] = ((RR_TurnInfo >> 8) & 0xFF);
            I2cRegBank[24] = ServoControl[10] = (RR_TurnInfo & 0xFF);

            //Steer Front wheels straight while going backward
            //FL                  FR
            I2cRegBank[17] = I2cRegBank[21] = 0xC0;
            I2cRegBank[18] = I2cRegBank[22] = 0x00;
            
            ServoControl[3] = ServoControl[7] =  0xC0;
            ServoControl[4] = ServoControl[8] = 0x00;

            if(turnServo(MV_BAKWARD_X_REG))
            {
                MV_DIR_PORT = MV_BAKWARD_X_REG;
                I2cRegBank[0]  = MDIR_AKR_STEER_Q4;
            }
          }
          
        }
         
      if(PWM_ON == false)
      {
        setupPWM16();
      }
    
      for(int i=0; i<15; i++)
      {c[i] = '\0';}
      
//      Serial.write(0xBB);
      return;
  }
  else 
  if(index == 10 && (c[0] == 'S' && c[1] == 'S' && c[8] == 'S' && c[9] == 'P'))
  {
        index = 0;
//        Serial.println("Commanmd Evaluating");
        LastControlRecieved = micros();
        //Highest bit indicates sign of the rotation
        //1 for positive(Forward) and 0 for negative(BackWard)
        uint16_t LinearXInfo  = ((c[2] << 8) | c[3]);
        //1 for positive(right turn) and 0 for negative(left turn)
        uint16_t AngularZInfo = ((c[4] << 8) | c[5]);
        
        //1 for positive(left Move) and 0 for negative(right Move)
        uint16_t LinearYInfo = ((c[6] << 8) | c[7]);


        int LinearXDirection = ExtractDirection(LinearXInfo);
        int LinearYDirection = ExtractDirection(LinearYInfo);
        int AngularZDirection = ExtractDirection(AngularZInfo);
        
        double LinearXVelocity = ExtractLinearVelocity(LinearXInfo);
        double LinearYVelocity = ExtractLinearVelocity(LinearYInfo);
         //AngularZvelocity only valid for LinearXVelocity == 0 || LinearXVelocity != 0
         //AngularZvelocity will not work in combination with LinearYVelocity
        double AngularZVelocity = ExtractAngularVelocity(AngularZInfo);


        //MV_DIR_PORT = MV_NOP_REG;
       // I2cRegBank[0] = MDIR_STOP;
    
        if(LinearXVelocity == 0)
        {
          //Priority for AngularZ,..LinearY is ignored for AngularZ!=0
          if(AngularZVelocity != 0)
          {
                    
            float Wheel2Wheel_Circle_Dia = 365.0; //mm
            float Circumferance = (PI * Wheel2Wheel_Circle_Dia);
            float mmPerRadian = Circumferance/(2*PI);
            float TurnVelocity = mmPerRadian * AngularZVelocity;

             //Set Requested Velocity LinearXVelocity
            //FL                RL              FR              RR
            I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = (((int)TurnVelocity >> 8) & 0xFF);
            I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = (((int)TurnVelocity) & 0xFF);
 

            uint16_t PWM = EstimatePWMFromVelocity(TurnVelocity);
            
            //Set Initial Speed PWM values, Will be modified by Ododmeter
            //FL                  RL                FR              RR
            I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = ((PWM >> 8) & 0xFF);
            I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = ((PWM) & 0xFF);


            //Set Initial Speed PWM values, will be updated from I2cRegBank
            RLMotorDelay = PWM;
            FLMotorDelay = PWM;
            RRMotorDelay = PWM;
            FRMotorDelay = PWM;


             
            //Current Servo delta angles
            //FL                  RL                FR              RR
            I2cRegBank[17]  = 0x5A;
            I2cRegBank[18]  = 0xC0;
            I2cRegBank[19]  = 0x97;
            I2cRegBank[20]  = 0x9A;
            I2cRegBank[21]  = 0x9A;
            I2cRegBank[22]  = 0x9A;
            I2cRegBank[23]  = 0x57;
            I2cRegBank[24]  = 0xC0;

            
            ServoControl[3]  = 0x5A;
            ServoControl[4]  = 0xC0;
            ServoControl[5]  = 0x97;
            ServoControl[6]  = 0x9A;
            ServoControl[7]  = 0x9A;
            ServoControl[8]  = 0x9A;
            ServoControl[9]  = 0x57;
            ServoControl[10]  = 0xC0;


             if(AngularZDirection == 1 &&
             turnServo(MV_TURN_Z_ANTI_CLOCKWISE_REG))
              {
                MV_DIR_PORT = MV_TURN_Z_ANTI_CLOCKWISE_REG;
                I2cRegBank[0]  = MDIR_TURN_ANTICLOCKWISE;
              }
              else
              if(AngularZDirection == -1 &&
             turnServo(MV_TURN_Z_CLOCKWISE_REG))
              {
                MV_DIR_PORT = MV_TURN_Z_CLOCKWISE_REG;
                I2cRegBank[0]  = MDIR_TURN_CLOCKWISE;
              }
            
            
              if(PWM_ON == false)
              {
                setupPWM16();
              }
          }
          else
          if(LinearYVelocity != 0)
          {

             //Set Requested Velocity LinearYVelocity
            //FL                RL              FR              RR
            I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = (((int)LinearYVelocity >> 8) & 0xFF);
            I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = (((int)LinearYVelocity) & 0xFF);
 

            uint16_t PWM = EstimatePWMFromVelocity(LinearYVelocity);
            
            //Set Initial Speed PWM values, Will be modified by Ododmeter
            //FL                  RL                FR              RR
            I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = ((PWM >> 8) & 0xFF);
            I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = ((PWM) & 0xFF);


            //Set Initial Speed PWM values, will be updated from I2cRegBank
            RLMotorDelay = PWM;
            FLMotorDelay = PWM;
            RRMotorDelay = PWM;
            FRMotorDelay = PWM;

            
            //Current Servo delta angles
            //FL                  RL                FR              RR
            I2cRegBank[17]  = 0x78;
            I2cRegBank[18]  = 0x10;
            I2cRegBank[19]  = 0xB3;
            I2cRegBank[20]  = 0xD0;
            I2cRegBank[21]  = 0xB5;
            I2cRegBank[22]  = 0x10;
            I2cRegBank[23]  = 0x73;
            I2cRegBank[24]  = 0xD0;

            
            ServoControl[3]  = 0x77;
            ServoControl[4]  = 0xD0;
            ServoControl[5]  = 0xB3;
            ServoControl[6]  = 0xD0;
            ServoControl[7]  = 0xB5;
            ServoControl[8]  = 0x10;
            ServoControl[9]  = 0x73;
            ServoControl[10]  = 0xD0;

            

            
               if(LinearYDirection == 1 &&
                  turnServo(MV_LEFT_Y_REG))
              {
                MV_DIR_PORT = MV_LEFT_Y_REG;
                I2cRegBank[0]  = MDIR_MOVE_LEFT;
              }
              else
              if(LinearYDirection == -1 &&
                turnServo(MV_RIGHT_Y_REG))
              {
                MV_DIR_PORT = MV_RIGHT_Y_REG;
                I2cRegBank[0]  = MDIR_MOVE_RIGHT;
              }
            
            
            if(PWM_ON == false)
            {
              setupPWM16();
            }

              
          }
          else
          {

            StopMotion();
            Serial.write(0xCC);
              //HOLD DC Drivers
//              MV_DIR_PORT = MV_NOP_REG;
//              I2cRegBank[0] = MDIR_STOP;
//              
//              //Stop PWM Timer
//              if(PWM_ON == true)
//              {
//                StopPWM();
//              }
//    
//              //Set Requested Velocity to Zero
//              //FL RL FR RR
//              I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = 0;
//              I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = 0;
//    
//              I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = 0;
//              I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = 0;
//    
//              I2cRegBank[17] = I2cRegBank[19] = I2cRegBank[21] = I2cRegBank[23] = 0;
//              I2cRegBank[18] = I2cRegBank[20] = I2cRegBank[22] = I2cRegBank[24] = 0;
//                
//    
//    
//              //Make PWM Zero
//              analogWrite16(PWM_RL,0);
//              analogWrite16(PWM_FR,0);
//              analogWrite16(PWM_RR,0);
//              analogWrite16(PWM_FL,0);
//      
//              //Disable Servos
////              ServoControl[3] = ServoControl[5] = ServoControl[7] = ServoControl[9] = 0x00;
////              ServoControl[4] = ServoControl[6] = ServoControl[8] = ServoControl[10] = 0x00;
////      
////              Serial1.write(ServoControl,14);

              
          }
        }
        else
        {
  
          //Requested to move straight along X direction
          if(AngularZVelocity == 0)
          {
            
            //Set Requested Velocity LinearXVelocity
            //FL                RL              FR              RR
            I2cRegBank[1] = I2cRegBank[3] = I2cRegBank[5] = I2cRegBank[7] = (((int)LinearXVelocity >> 8) & 0xFF);
            I2cRegBank[2] = I2cRegBank[4] = I2cRegBank[6] = I2cRegBank[8] = (((int)LinearXVelocity) & 0xFF);
 

            uint16_t PWM = EstimatePWMFromVelocity(LinearXVelocity);
            
            //Set Initial Speed PWM values, Will be modified by Ododmeter
            //FL                  RL                FR              RR
            I2cRegBank[9] = I2cRegBank[11] = I2cRegBank[13] = I2cRegBank[15] = ((PWM >> 8) & 0xFF);
            I2cRegBank[10] = I2cRegBank[12] = I2cRegBank[14] = I2cRegBank[16] = ((PWM) & 0xFF);


            //Set Initial Speed PWM values, will be updated from I2cRegBank
            RLMotorDelay = PWM;
            FLMotorDelay = PWM;
            RRMotorDelay = PWM;
            FRMotorDelay = PWM;

           

            
            //Current Servo delta angles
            //FL                  RL                FR              RR
            I2cRegBank[17] = I2cRegBank[19] = I2cRegBank[21] = I2cRegBank[23] = 0xC0;
            I2cRegBank[18] = I2cRegBank[20] = I2cRegBank[22] = I2cRegBank[24] = 0x00;
          
            ServoControl[3] = ServoControl[5] = ServoControl[7] = ServoControl[9] = 0xC0;
            ServoControl[4] = ServoControl[6] = ServoControl[8] = ServoControl[10] = 0x00;

            

            
               if(LinearXDirection == 1 &&
                turnServo(MV_FORWARD_X_REG))
              {
                MV_DIR_PORT = MV_FORWARD_X_REG;
                I2cRegBank[0]  = MDIR_MOVE_UP;
              }
              else
              if(LinearXDirection == -1 &&
                turnServo(MV_BAKWARD_X_REG))
              {
                MV_DIR_PORT = MV_BAKWARD_X_REG;
                I2cRegBank[0]  = MDIR_MOVE_DOWN;
              }
            
            
          }
          else
          {
            double OMEGA    = AngularZVelocity; //in rad/sec //..??Convert scaled(by 100) Angular speed to decimal
            double VELOCITY = LinearXVelocity * 1.0; // in mm/sec
            
            // Linear Velocity = Angular velocity * radius
            double r = (VELOCITY/OMEGA)/10; //divide by 10 to get r in cm

         
            
//            Serial.print("radius : ");
//            Serial.println(r, DEC);

            //Amount of turn angle for Front wheel of inner rotation circle
            //added abs for radius value lies in between middle circle and inner circle
            double cosPhi = abs(r-11.5)/(sqrt( (r*r) - (23*r) + 264.5));
            //Amount of turn angle for Front wheel of outer rotation circle
            double cosAlpha = (r+11.5)/(sqrt( (r*r) + (23*r) + 264.5));

            
//            Serial.print("cosPhi : ");
//            Serial.println(cosPhi, DEC);
//            Serial.print("cosAlpha : ");
//            Serial.println(cosAlpha, DEC);
  
            double ViWheel = (VELOCITY / cosPhi);
            double VoWheel = (VELOCITY / cosAlpha);
            
//            Serial.print("ViWheel : ");
//            Serial.println(ViWheel, DEC);
//            Serial.print("VoWheel : ");
//            Serial.println(VoWheel, DEC);

            uint16_t ViPWM = EstimatePWMFromVelocity(ViWheel);
            uint16_t VoPWM = EstimatePWMFromVelocity(VoWheel);
            
//            Serial.print("ViPWM : ");
//            Serial.println(ViPWM, DEC);
//            Serial.print("VoPWM : ");
//            Serial.println(VoPWM, DEC);

            //Amount of turn angle for Front wheel of inner rotation circle
            //Note : Rear wheels should rotate in opposite direction
            double Phi = acos(cosPhi);
            //Amount of turn angle for Front wheel of outer rotation circle
            //Note : Rear wheels should rotate in opposite direction
            double Alpha = acos(cosAlpha);
            
//            Serial.print("Phi : ");
//            Serial.println(Phi, DEC);
//            Serial.print("Alpha : ");
//            Serial.println(Alpha, DEC);
            
            double Phi_Scaled = acos(cosPhi) * 10000;
            double Alpha_Scaled = acos(cosAlpha) * 10000;
            
//            Serial.print("Phi_Scaled : ");
//            Serial.println(Phi_Scaled, DEC);
//            Serial.print("Alpha_Scaled : ");
//            Serial.println(Alpha_Scaled, DEC);

            //Make Right Turn
            if(AngularZDirection == -1)
            {
                //Set required Inner circle wheels Velocity
                //FR              RR
                I2cRegBank[5] = I2cRegBank[7] = (((int)ViWheel >> 8) & 0xFF);
                I2cRegBank[6] = I2cRegBank[8] = (((int)ViWheel) & 0xFF);

                //Set required Outer circle wheels Velocity
                //FL                RL         
                I2cRegBank[1] = I2cRegBank[3] = (((int)VoWheel >> 8) & 0xFF);
                I2cRegBank[2] = I2cRegBank[4] = (((int)VoWheel) & 0xFF);
                
                //Set Initial Inner circle wheels PWM values, Will be modified by Ododmeter
                //FR              RR
                I2cRegBank[13] = I2cRegBank[15] = ((ViPWM >> 8) & 0xFF);
                I2cRegBank[14] = I2cRegBank[16] = ((ViPWM) & 0xFF);
                
                //Set Initial Outer circle wheels PWM values, Will be modified by Ododmeter
                //FL                  RL
                I2cRegBank[9] = I2cRegBank[11]  = ((VoPWM >> 8) & 0xFF);
                I2cRegBank[10] = I2cRegBank[12] = ((VoPWM) & 0xFF);

      
                //Set Initial Speed PWM values, will be updated from I2cRegBank
                RRMotorDelay = ViPWM;
                FRMotorDelay = ViPWM;
                
                RLMotorDelay = VoPWM;
                FLMotorDelay = VoPWM;

                //Wheels steered in opposite Ditection to go in inner circle
                uint16_t FR_TurnInfo = GetTurnInfo(1,Phi_Scaled);
                uint16_t RR_TurnInfo = GetTurnInfo(2,Phi_Scaled);
                
                //Wheels steered in opposite Ditection to go in outer circle
                uint16_t FL_TurnInfo = GetTurnInfo(1,Alpha_Scaled);
                uint16_t RL_TurnInfo = GetTurnInfo(2,Alpha_Scaled);

//                Serial.print("FR_TurnInfo : ");
//                Serial.println(FR_TurnInfo, DEC);
//                Serial.print("RR_TurnInfo : ");
//                Serial.println(RR_TurnInfo, DEC);
//                Serial.print("FL_TurnInfo : ");
//                Serial.println(FL_TurnInfo, DEC);
//                Serial.print("RL_TurnInfo : ");
//                Serial.println(RL_TurnInfo, DEC);

                I2cRegBank[17] = ServoControl[3] = ((FL_TurnInfo >> 8) & 0xFF);
                I2cRegBank[18] = ServoControl[4] = (FL_TurnInfo & 0xFF);
                
                I2cRegBank[19] = ServoControl[5] = ((RL_TurnInfo >> 8) & 0xFF);
                I2cRegBank[20] = ServoControl[6] = (RL_TurnInfo & 0xFF);
                
                I2cRegBank[21] = ServoControl[7] = ((FR_TurnInfo >> 8) & 0xFF);
                I2cRegBank[22] = ServoControl[8] = (FR_TurnInfo & 0xFF);
                
                I2cRegBank[23] = ServoControl[9] = ((RR_TurnInfo >> 8) & 0xFF);
                I2cRegBank[24] = ServoControl[10] = (RR_TurnInfo & 0xFF);

                
               
                     if(LinearXDirection == 1 &&
                        turnServo(MV_FORWARD_X_REG))
                    {
                      I2cRegBank[0]  = MDIR_STEER_Q2;
                    }
                    else
                    if(LinearXDirection == -1 &&
                       turnServo(MV_BAKWARD_X_REG))
                    {
                      I2cRegBank[0]  = MDIR_STEER_Q4;
                    }
                
            }
            else
            //Make Left Turn
            if(AngularZDirection == 1)
            {
                
               //Set required Outer circle wheels Velocity
                //FR              RR
                I2cRegBank[5] = I2cRegBank[7] = (((int)VoWheel >> 8) & 0xFF);
                I2cRegBank[6] = I2cRegBank[8] = (((int)VoWheel) & 0xFF);

                //Set required Inner circle wheels Velocity
                //FL                RL         
                I2cRegBank[1] = I2cRegBank[3] = (((int)ViWheel >> 8) & 0xFF);
                I2cRegBank[2] = I2cRegBank[4] = (((int)ViWheel) & 0xFF);
                
                //Set Initial Outer circle wheels PWM values, Will be modified by Ododmeter
                //FR              RR
                I2cRegBank[13] = I2cRegBank[15] = ((VoPWM >> 8) & 0xFF);
                I2cRegBank[14] = I2cRegBank[16] = ((VoPWM) & 0xFF);
                
                //Set Initial Inner circle wheels PWM values, Will be modified by Ododmeter
                //FL                  RL
                I2cRegBank[9] = I2cRegBank[11]  = ((ViPWM >> 8) & 0xFF);
                I2cRegBank[10] = I2cRegBank[12] = ((ViPWM) & 0xFF);

      
                //Set Initial Speed PWM values, will be updated from I2cRegBank
                RRMotorDelay = VoPWM;
                FRMotorDelay = VoPWM;
                
                RLMotorDelay = ViPWM;
                FLMotorDelay = ViPWM;

                //Wheels steered in opposite Ditection to go in outer circle
                uint16_t FR_TurnInfo = GetTurnInfo(2,Alpha_Scaled);
                uint16_t RR_TurnInfo = GetTurnInfo(1,Alpha_Scaled);
                
                //Wheels steered in opposite Ditection to go in inner circle
                uint16_t FL_TurnInfo = GetTurnInfo(2,Phi_Scaled);
                uint16_t RL_TurnInfo = GetTurnInfo(1,Phi_Scaled);

                I2cRegBank[17] = ServoControl[3] = ((FL_TurnInfo >> 8) & 0xFF);
                I2cRegBank[18] = ServoControl[4] = (FL_TurnInfo & 0xFF);
                
                I2cRegBank[19] = ServoControl[5] = ((RL_TurnInfo >> 8) & 0xFF);
                I2cRegBank[20] = ServoControl[6] = (RL_TurnInfo & 0xFF);
                
                I2cRegBank[21] = ServoControl[7] = ((FR_TurnInfo >> 8) & 0xFF);
                I2cRegBank[22] = ServoControl[8] = (FR_TurnInfo & 0xFF);
                
                I2cRegBank[23] = ServoControl[9] = ((RR_TurnInfo >> 8) & 0xFF);
                I2cRegBank[24] = ServoControl[10] = (RR_TurnInfo & 0xFF);

                
                
                    if(LinearXDirection == 1 &&
                      turnServo(MV_FORWARD_X_REG))
                    {
                      I2cRegBank[0]  = MDIR_STEER_Q1;
                    }
                    else
                    if(LinearXDirection == -1 &&
                      turnServo(MV_BAKWARD_X_REG))
                    {
                      I2cRegBank[0]  = MDIR_STEER_Q3;
                    }
                
            }

            if(LinearXDirection == 1)
            {
                MV_DIR_PORT = MV_FORWARD_X_REG;
            }
            else
            if(LinearXDirection == -1)
            {
                MV_DIR_PORT = MV_BAKWARD_X_REG;
            }
            
          }
  
  
            if(PWM_ON == false)
            {
              setupPWM16();
            }
        }

      for(int i=0; i<15; i++)
      {c[i] = '\0';}
      
      LastControlRecieved = micros();
//      Serial.write(0xBB);
      return;
  }

 }

}
