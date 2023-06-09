#include <PinChangeInt.h>

#include <PID_v1.h>
#include <Wire.h>
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/


#define MAKEBYTE_16BIT(X,H,L) {\
if (H != 0x7F)\
{\
  X=H;\
  X = X<<8;\
}\
X |= L;\
}   



//Wheel Comms Module I2C address
#define WHL_COM_ADD 10

//Wheel Controller Module I2C address
#define WHL_CON_ADD 11



//Length measuremetns are in millimeter
#define WHEEL_DIA  110
#define ENCODER_SLOT_COUNT 100

#define WHEEL_CIRCUMFERANCE (WHEEL_DIA*3.14) //pi*2r

//Number of RISING pulses per rotation
#define COUNTS_PER_ROTATION = 100 

#define DISTANCE_PER_COUNT (WHEEL_CIRCUMFERANCE / 100)

#define DISTANCE_PER_COUNT_MTS DISTANCE_PER_COUNT/1000

//Robot Motion Modes-- refer Motion Controller module
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


//Looking from back of the Robot
#define ENCODER_PIN_FL 2
#define ENCODER_PIN_FR 3
#define ENCODER_PIN_RL 7
#define ENCODER_PIN_RR 6

#define ANALOG_PIN_FL A2
#define ANALOG_PIN_FR A0
#define ANALOG_PIN_RL A6
#define ANALOG_PIN_RR A7

#define COMMS_ODO_REG_BANK_FL 0
#define COMMS_ODO_REG_BANK_FR 12
#define COMMS_ODO_REG_BANK_RL 24
#define COMMS_ODO_REG_BANK_RR 36
#define COMMS_ODO_REG_BANK_YAW 48
#define COMMS_ODO_REG_BANK_W 50
#define COMMS_ODO_REG_BANK_X 52
#define COMMS_ODO_REG_BANK_Y 56
#define COMMS_ODO_REG_BANK_VX 60
#define COMMS_ODO_REG_BANK_VY 64
#define COMMS_ODO_REG_BANK_THETA 68
#define COMMS_ODO_REG_BANK_OMEGA 70
#define COMMS_ODO_REG_BANK_STAT 72



#define REG_MDIR 0

#define REG_VEL_FL 01
#define REG_VEL_RL 03
#define REG_VEL_FR 05
#define REG_VEL_RR 07
#define REG_VEL_LEN 02


#define REG_PWM_FL 9
#define REG_PWM_RL 11
#define REG_PWM_FR 13
#define REG_PWM_RR 15
#define REG_PWM_LEN 02


#define REG_ANG_FL 17
#define REG_ANG_RL 19
#define REG_ANG_FR 21
#define REG_ANG_RR 23
#define REG_ANG_LEN 02

#define VEL_BUFF_SIZE 10

struct ODO_DATA
{
  //Recorded Parameters
//  unsigned long KiloMeters;
//  unsigned int Meters;
//  unsigned int MilliMeters;
  double KiloMeters;
  double Meters;
  double MilliMeters;
  int Turn;
  unsigned int Velocity;

  //PID Control
  double aggKp=4, aggKi=0.2, aggKd=1;
  double consKp=1, consKi=0.05, consKd=0.25;
  double TargetPWM;
  double CurrentPWM;
  double SetVelocity;
  PID * SPEED_CNTRL;

  //Runtime Parameters
  unsigned int RequestedVelocity;
  long EncoderTiming[2];
  unsigned int EncoderTimingIndex = 0;
  byte Vel_Buf_Index = 0;
  uint16_t Vel_Buf[VEL_BUFF_SIZE];
  int ROT_DIR_A;
  int ROT_DIR_B;
  int TickCount = 0;
} ODO_FL, ODO_FR, ODO_RL, ODO_RR;




void FLCounter() {
  ODO_FL.TickCount++;
  ODO_FL.EncoderTiming[ODO_FL.EncoderTimingIndex] = micros();
  ODO_FL.EncoderTimingIndex ^= 1;

  if(ODO_FL.Vel_Buf_Index == VEL_BUFF_SIZE) ODO_FL.Vel_Buf_Index = 0;
  
  uint16_t Velocity =((DISTANCE_PER_COUNT*1.0) / (abs(ODO_FL.EncoderTiming[0] - ODO_FL.EncoderTiming[1])/1000000.0));
  ODO_FL.Vel_Buf[0] = Velocity;
  //ODO_FL.Vel_Buf[ODO_FL.Vel_Buf_Index++] = Velocity;
}

void FRCounter() {
  ODO_FR.TickCount++;
  ODO_FR.EncoderTiming[ODO_FR.EncoderTimingIndex] = micros();
  ODO_FR.EncoderTimingIndex^= 1 << 0;

   if(ODO_FR.Vel_Buf_Index == VEL_BUFF_SIZE) ODO_FR.Vel_Buf_Index = 0;
  
  uint16_t Velocity = ((DISTANCE_PER_COUNT*1.0) / (abs(ODO_FR.EncoderTiming[0] - ODO_FR.EncoderTiming[1])/1000000.0));
  ODO_FR.Vel_Buf[0] = Velocity;
  //ODO_FR.Vel_Buf[ODO_FR.Vel_Buf_Index++] = Velocity;
}

void RLCounter() {
  ODO_RL.TickCount++;
  ODO_RL.EncoderTiming[ODO_RL.EncoderTimingIndex] = micros();
  ODO_RL.EncoderTimingIndex^= 1 << 0;

  if(ODO_RL.Vel_Buf_Index == VEL_BUFF_SIZE) ODO_RL.Vel_Buf_Index = 0;
   uint16_t Velocity = ((DISTANCE_PER_COUNT*1.0) / (abs(ODO_RL.EncoderTiming[0] - ODO_RL.EncoderTiming[1])/1000000.0));
  ODO_RL.Vel_Buf[0] = Velocity;
  //ODO_RL.Vel_Buf[ODO_RL.Vel_Buf_Index++] = Velocity;

}

void RRCounter() {
  ODO_RR.TickCount++;
  ODO_RR.EncoderTiming[ODO_RR.EncoderTimingIndex] = micros();
  ODO_RR.EncoderTimingIndex^= 1 << 0;

  if(ODO_RR.Vel_Buf_Index == VEL_BUFF_SIZE) ODO_RR.Vel_Buf_Index = 0;
   uint16_t Velocity = ((DISTANCE_PER_COUNT*1.0) / (abs(ODO_RR.EncoderTiming[0] - ODO_RR.EncoderTiming[1])/1000000.0));
  ODO_RR.Vel_Buf[0] = Velocity;
  //ODO_RR.Vel_Buf[ODO_RR.Vel_Buf_Index++] = Velocity;
}

#define FL_ROT_DIR_A 4
#define FL_ROT_DIR_B 5

#define RL_ROT_DIR_A 8
#define RL_ROT_DIR_B 9

#define RR_ROT_DIR_A 10
#define RR_ROT_DIR_B 11

#define FR_ROT_DIR_A 12
#define FR_ROT_DIR_B 13


// the setup function runs once when you press reset or power the board
void setup() {

  delay(1000);
   Wire.begin();
   
   Serial.begin(500000);
   
   pinMode(FL_ROT_DIR_A, INPUT);//FL
   pinMode(FL_ROT_DIR_B, INPUT);
   pinMode(RL_ROT_DIR_A, INPUT);//RL
   pinMode(RL_ROT_DIR_B, INPUT);
   pinMode(RR_ROT_DIR_A, INPUT);//RR
   pinMode(RR_ROT_DIR_B, INPUT);
   pinMode(FR_ROT_DIR_A, INPUT);//FR
   pinMode(FR_ROT_DIR_B, INPUT);

   ODO_FL.ROT_DIR_A = FL_ROT_DIR_A;  ODO_FL.ROT_DIR_B = FL_ROT_DIR_B;
   ODO_FR.ROT_DIR_A = FR_ROT_DIR_A;  ODO_FR.ROT_DIR_B = FR_ROT_DIR_B;
   ODO_RL.ROT_DIR_A = RL_ROT_DIR_A;  ODO_RL.ROT_DIR_B = RL_ROT_DIR_B;
   ODO_RR.ROT_DIR_A = RR_ROT_DIR_A;  ODO_RR.ROT_DIR_B = RR_ROT_DIR_B;

   ODO_FL.SPEED_CNTRL = new PID(&ODO_FL.CurrentPWM, &ODO_FL.TargetPWM, &ODO_FL.SetVelocity, ODO_FL.consKp, ODO_FL.consKi, ODO_FL.consKd, DIRECT);
   ODO_FR.SPEED_CNTRL = new PID(&ODO_FR.CurrentPWM, &ODO_FR.TargetPWM, &ODO_FR.SetVelocity, ODO_FR.consKp, ODO_FR.consKi, ODO_FR.consKd, DIRECT);
   ODO_RL.SPEED_CNTRL = new PID(&ODO_RL.CurrentPWM, &ODO_RL.TargetPWM, &ODO_RL.SetVelocity, ODO_RL.consKp, ODO_RL.consKi, ODO_RL.consKd, DIRECT);
   ODO_RR.SPEED_CNTRL = new PID(&ODO_RR.CurrentPWM, &ODO_RR.TargetPWM, &ODO_RR.SetVelocity, ODO_RR.consKp, ODO_RR.consKi, ODO_RR.consKd, DIRECT);
  
  pinMode(ENCODER_PIN_FL, INPUT); digitalWrite(ENCODER_PIN_FL, HIGH);
  PCintPort::attachInterrupt(ENCODER_PIN_FL, &FLCounter, RISING);
  pinMode(ENCODER_PIN_FR, INPUT); digitalWrite(ENCODER_PIN_FR, HIGH);
  PCintPort::attachInterrupt(ENCODER_PIN_FR, &FRCounter, RISING);
  pinMode(ENCODER_PIN_RL, INPUT); digitalWrite(ENCODER_PIN_RL, HIGH);
  PCintPort::attachInterrupt(ENCODER_PIN_RL, &RLCounter, RISING);
  pinMode(ENCODER_PIN_RR, INPUT); digitalWrite(ENCODER_PIN_RR, HIGH);
  PCintPort::attachInterrupt(ENCODER_PIN_RR, &RRCounter, RISING);

   ODO_FL.SPEED_CNTRL->SetMode(AUTOMATIC);
   ODO_FR.SPEED_CNTRL->SetMode(AUTOMATIC);
   ODO_RL.SPEED_CNTRL->SetMode(AUTOMATIC);
   ODO_RR.SPEED_CNTRL->SetMode(AUTOMATIC);
}

double GetInMeters(struct ODO_DATA* ODO_REF)
{
  
  double mm = ODO_REF->MilliMeters;
  return  (ODO_REF->KiloMeters * 1000) + (ODO_REF->Meters) + (mm/1000);
}

void SetODO(int newCount, int newTurn, struct ODO_DATA* ODO_REF)
{
   double Distance = newCount * DISTANCE_PER_COUNT; //in millimeter

   //calculate distance total distance
   ODO_REF->MilliMeters = ODO_REF->MilliMeters + Distance;
   if(ODO_REF->MilliMeters/1000 > 0)
   {
      ODO_REF->Meters = ODO_REF->Meters + (ODO_REF->MilliMeters/1000);
      ODO_REF->MilliMeters = (ODO_REF->MilliMeters - ((ODO_REF->MilliMeters/1000)*1000)) ;
   }
   if(ODO_REF->Meters/1000 > 0)
   {
      ODO_REF->KiloMeters = ODO_REF->KiloMeters + (ODO_REF->Meters/1000);
      ODO_REF->Meters = (ODO_REF->Meters - ((ODO_REF->Meters/1000)*1000)) ;
   }

  
   ODO_REF->Velocity = 0;
   if(digitalRead(ODO_REF->ROT_DIR_A) != digitalRead(ODO_REF->ROT_DIR_B) &&  
      abs(micros() - ODO_REF->EncoderTiming[ODO_FL.EncoderTimingIndex])/1000 < 500)
   {
//     for(int i=0; i<VEL_BUFF_SIZE; i++)
//     {
//       ODO_REF->Velocity += ODO_REF->Vel_Buf[i];
//     }
//     ODO_REF->Velocity /= VEL_BUFF_SIZE;

      ODO_REF->Velocity = ODO_REF->Vel_Buf[0];
   }
   else
   {
    for(int i=0; i<VEL_BUFF_SIZE; i++)
     {
       ODO_REF->Vel_Buf[i] = 0;
     }
   }
   
   ODO_REF->Turn = newTurn;
}

void Write_ODOData(int Address, struct ODO_DATA* ODO_REF)
{
  Wire.beginTransmission(WHL_COM_ADD); // transmit to device #8
  Wire.write(Address);
  Wire.write(12); 
  Wire.write((unsigned long)(ODO_REF->KiloMeters) & 0xFF);
  Wire.write((unsigned long)(ODO_REF->KiloMeters)>>8 & 0xFF);
  Wire.write((unsigned long)(ODO_REF->KiloMeters)>>16 & 0xFF);
  Wire.write((unsigned long)(ODO_REF->KiloMeters)>>24 & 0xFF);
  Wire.write((unsigned long)(ODO_REF->Meters) & 0xFF);
  Wire.write((unsigned long)(ODO_REF->Meters)>>8 & 0xFF);
  Wire.write((unsigned long)(ODO_REF->MilliMeters) & 0xFF);
  Wire.write((unsigned long)(ODO_REF->MilliMeters)>>8 & 0xFF);
  Wire.write(ODO_REF->Turn & 0xFF);
  Wire.write(ODO_REF->Turn>>8 & 0xFF);
  Wire.write(ODO_REF->Velocity & 0xFF);
  Wire.write(ODO_REF->Velocity>>8 & 0xFF);
  Wire.endTransmission();    // stop transmitting
}

long MASK = 0xFF;

void Write_ODOMeasure(int Address, long X, long Y, long VX, long VY, uint16_t Theta, uint16_t AngVel)
{

  uint32_t XInfo = abs(X);
  if(X < 0) XInfo = XInfo | 0x80000000;
  
  uint32_t YInfo = abs(Y);
  if(Y < 0) YInfo = YInfo | 0x80000000;
  
  uint32_t VXInfo = abs(VX);
  if(VX < 0) VXInfo = VXInfo | 0x80000000;
  
  uint32_t VYInfo = abs(VY);
  if(VY < 0) VYInfo = VYInfo | 0x80000000;
  
  Wire.beginTransmission(WHL_COM_ADD); // transmit to device #8
  Wire.write(Address);
  Wire.write(21); 
  Wire.write(XInfo>>24 & 0xFF);
  Wire.write(XInfo>>16 & 0xFF);
  Wire.write(XInfo>>8 & 0xFF);
  Wire.write(XInfo & 0xFF);
  
  Wire.write(YInfo>>24 & 0xFF);
  Wire.write(YInfo>>16 & 0xFF);
  Wire.write(YInfo>>8 & 0xFF);
  Wire.write(YInfo & 0xFF);
  
  Wire.write(VXInfo>>24 & 0xFF);
  Wire.write(VXInfo>>16 & 0xFF);
  Wire.write(VXInfo>>8 & 0xFF);
  Wire.write(VXInfo & 0xFF);
  
  Wire.write(VYInfo>>24 & 0xFF);
  Wire.write(VYInfo>>16 & 0xFF);
  Wire.write(VYInfo>>8 & 0xFF);
  Wire.write(VYInfo & 0xFF);
  
  Wire.write(Theta>>8 & 0xFF);
  Wire.write(Theta & 0xFF);
  
  Wire.write(AngVel>>8 & 0xFF);
  Wire.write(AngVel & 0xFF);
  
  Wire.write(0x01);
  Wire.endTransmission();    // stop transmitting
}

long lastSendMicros = micros();


int _FLCount_Total = 0;
int _FRCount_Total  = 0;
int _RLCount_Total  = 0;
int _RRCount_Total  = 0;

//// the loop function runs over and over again forever
void loop() {

if(abs(micros() - lastSendMicros) > 10000)
{
  lastSendMicros = micros();
  
  int _FLCount  = ODO_FL.TickCount;
  int _FRCount  = ODO_FR.TickCount;
  int _RLCount  = ODO_RL.TickCount;
  int _RRCount  = ODO_RR.TickCount;

//  
//  _FLCount_Total+=_FLCount;
//  _FRCount_Total+=_FRCount;
//  _RLCount_Total+=_RLCount;
//  _RRCount_Total+=_RRCount;
//
//     Serial.print(":");
//    Serial.print(_FLCount_Total);
//    Serial.print(", ");
//    Serial.print(_FRCount_Total);
//    Serial.print(", ");
//    Serial.print(_RLCount_Total);
//    Serial.print(", ");
//    Serial.println(_RRCount_Total);
  
  ODO_FL.TickCount = 0;
  ODO_FR.TickCount = 0;
  ODO_RL.TickCount = 0;
  ODO_RR.TickCount = 0;
  
  SetODO(_FLCount, analogRead(ANALOG_PIN_FL), &ODO_FL);
  SetODO(_FRCount, analogRead(ANALOG_PIN_FR), &ODO_FR);
  SetODO(_RLCount, analogRead(ANALOG_PIN_RL), &ODO_RL);
  SetODO(_RRCount, analogRead(ANALOG_PIN_RR), &ODO_RR);

//  Write_ODOData(COMMS_ODO_REG_BANK_FL, &ODO_FL);
//  Write_ODOData(COMMS_ODO_REG_BANK_FR, &ODO_FR);
//  Write_ODOData(COMMS_ODO_REG_BANK_RR, &ODO_RL);
//  Write_ODOData(COMMS_ODO_REG_BANK_RL, &ODO_RR);

  
  ReadRequiredSpeed();
  
//    Serial.print(":");
//    Serial.print(ODO_FL.Velocity);
//    Serial.print(", ");
//    Serial.print(ODO_FR.Velocity);
//    Serial.print(", ");
//    Serial.print(ODO_RL.Velocity);
//    Serial.print(", ");
//    Serial.println(ODO_RR.Velocity);
//
//    Serial.print("!");
//    Serial.print(ODO_FL.RequestedVelocity);
//    Serial.print(", ");
//    Serial.print(ODO_FR.RequestedVelocity);
//    Serial.print(", ");
//    Serial.print(ODO_RL.RequestedVelocity);
//    Serial.print(", ");
//    Serial.println(ODO_RR.RequestedVelocity);

    AdjustSpeed();

    CalculateSpeeds();
}

//delay(50);

delayMicroseconds(10);

}


void WriteToWire(int DEV_ADDRESS, int REG_ADDRESS, int LENGTH, byte* Data)
{
   byte WRHeader[] = {REG_ADDRESS, LENGTH};
    
    Wire.beginTransmission(DEV_ADDRESS);
    Wire.write(WRHeader, 2);  
    Wire.write(Data, LENGTH);  
    Wire.endTransmission(); 
   
}


uint16_t ReadFromWire(int DEV_ADDRESS, int REG_ADDRESS, int LENGTH)
{
   byte Data[] = {(REG_ADDRESS|0x80), LENGTH};
    
    Wire.beginTransmission(DEV_ADDRESS);
    Wire.write(Data, 2);  
    Wire.endTransmission(); 
    
    Wire.requestFrom(DEV_ADDRESS, LENGTH);
    
     while(LENGTH < Wire.available());
     
     byte HIGHBYTE = Wire.read();
     byte LOWBYTE = Wire.read();
     uint16_t Value = 0;
     MAKEBYTE_16BIT(Value, HIGHBYTE, LOWBYTE);
     return Value;
}

byte ReadFromWire(int DEV_ADDRESS, int REG_ADDRESS)
{
   byte Data[] = {(REG_ADDRESS|0x80), 0x01};
    
    Wire.beginTransmission(DEV_ADDRESS);
    Wire.write(Data, 2);  
    Wire.endTransmission(); 
    
    Wire.requestFrom(DEV_ADDRESS, 1);
    
     while(1 < Wire.available());
     
     byte LOWBYTE = Wire.read();



     return LOWBYTE;
}

int ExtractDirection(uint16_t ServoInfo)
{
  
      switch((ServoInfo >> 14))
      {
        case 0:
        return 0xFF;
        case 1:
        return 1;
        case 2:
        return -1;
        case 3:
        return 0;
      }
}

double ExtractDeltaDegree(uint16_t ServoInfo)
{
   return (((double)(ServoInfo & 0x3FFF))/10000.0);
}


uint16_t readAngVelInfo()
{
   uint16_t AngVelInfo = ReadFromWire(WHL_COM_ADD, COMMS_ODO_REG_BANK_W ,2);
   
  return AngVelInfo;
}

uint16_t readYawInfo()
{
   uint16_t YAWInfo = ReadFromWire(WHL_COM_ADD, COMMS_ODO_REG_BANK_YAW ,2);
   
  return YAWInfo;
}

double convertYawInfoToRad(uint16_t YAWInfo)
{
   int sign = (YAWInfo>>15 == 0)? 1 : -1;

   double YAW_rad = (YAWInfo &  0x7FFF)/1000.0;

   return YAW_rad*sign;
}


long X = 0;
long Y = 0;
double lastFL_Mts = 0;
double lastFR_Mts = 0;
double lastRL_Mts = 0;
double lastRR_Mts = 0;
long lastSampled = micros();
double lastSampledYaw  =0;
void CalculateSpeeds()
{
      double sampleFL_Mts = GetInMeters(&ODO_FL);
      double sampleFR_Mts = GetInMeters(&ODO_FR);
      double sampleRL_Mts = GetInMeters(&ODO_RL);
      double sampleRR_Mts = GetInMeters(&ODO_RR);
      long   sampledSec = micros();

      byte MDIR =  ReadFromWire(WHL_CON_ADD, REG_MDIR);
      uint8_t ODOWriteStat = ReadFromWire(WHL_COM_ADD, COMMS_ODO_REG_BANK_STAT);
      uint16_t AngVelInfo = readAngVelInfo();
      uint16_t YawInfo = readYawInfo();
      double Yaw = convertYawInfoToRad(YawInfo);
      if((abs(abs(lastSampledYaw) - abs(Yaw)) > PI/6) && abs(micros() - lastSampled)  < 100000)
      {
        return;
      }
      

      double diffFL_Mts = abs(lastFL_Mts - sampleFL_Mts)*1000;
      double diffRL_Mts = abs(lastRL_Mts - sampleRL_Mts)*1000;
      double diffFR_Mts = abs(lastFR_Mts - sampleFR_Mts)*1000;
      double diffRR_Mts = abs(lastRR_Mts - sampleRR_Mts)*1000;
      double diffSec = abs(sampledSec - lastSampled)/1000000.0 ;

//       Serial.print(":");
//    Serial.print(diffSec);
//    Serial.print(", ");
//    Serial.print(diffFL_Mts);
//    Serial.print(", ");
//    Serial.print(diffRL_Mts);
//    Serial.print(", ");
//    Serial.print(diffRR_Mts);
//    Serial.print(", ");
//    Serial.println(diffRR_Mts);
    
      if(ODOWriteStat == 0 && abs(Yaw) < 3.14 && diffFL_Mts > DISTANCE_PER_COUNT  && diffRL_Mts > DISTANCE_PER_COUNT && diffFR_Mts > DISTANCE_PER_COUNT && diffRR_Mts > DISTANCE_PER_COUNT)
      {
        
      lastFL_Mts = sampleFL_Mts;
      lastFR_Mts = sampleFR_Mts;
      lastRL_Mts = sampleRL_Mts;
      lastRR_Mts = sampleRR_Mts;
      lastSampled = sampledSec;

      
      uint16_t FL_ANG_Info = ReadFromWire(WHL_CON_ADD, REG_ANG_FL, REG_ANG_LEN);
      uint16_t RL_ANG_Info = ReadFromWire(WHL_CON_ADD, REG_ANG_RL, REG_ANG_LEN);
      uint16_t FR_ANG_Info = ReadFromWire(WHL_CON_ADD, REG_ANG_FR, REG_ANG_LEN);
      uint16_t RR_ANG_Info = ReadFromWire(WHL_CON_ADD, REG_ANG_RR, REG_ANG_LEN);
  
      double  servoFL_Delta =  ExtractDeltaDegree(FL_ANG_Info);
      double  servoRL_Delta =  ExtractDeltaDegree(RL_ANG_Info);
      double  servoFR_Delta =  ExtractDeltaDegree(FR_ANG_Info);
      double  servoRR_Delta =  ExtractDeltaDegree(RR_ANG_Info);
      
      int   servoFL_DIR = ExtractDirection(FL_ANG_Info);
      int   servoRL_DIR = ExtractDirection(RL_ANG_Info);
      int   servoFR_DIR = ExtractDirection(FR_ANG_Info);
      int   servoRR_DIR = ExtractDirection(RR_ANG_Info);

      
  
      double Vx_Sum = 0;
      double Vy_Sum = 0;
      
      double Vxr_Sum = 0;
      double Vxf_Sum = 0;
      
      double Vyr_Sum = 0;
      double Vyf_Sum = 0;
      
      int Avg_Count = 4;
      int Avg_Steer_Count = 2;

      double Vfl = diffFL_Mts/diffSec;
      double Vfr = diffFR_Mts/diffSec;
      double Vrl = diffRL_Mts/diffSec;
      double Vrr = diffRR_Mts/diffSec;

//      Serial.print("V:");
//      Serial.print(Vfl);
//      Serial.print(", ");
//      Serial.print(Vfr);
//      Serial.print(", ");
//      Serial.print(Vrl);
//      Serial.print(", ");
//      Serial.println(Vrr);
            
      double Vx_FL = abs(cos(servoFL_Delta) * Vfl);
      double Vx_RL = abs(cos(servoRL_Delta) * Vrl);
      double Vx_FR = abs(cos(servoFR_Delta) * Vfr);
      double Vx_RR = abs(cos(servoRR_Delta) * Vrr);

      
//      Serial.print("Vx:");
//      Serial.print(Vx_FL);
//      Serial.print(", ");
//      Serial.print(Vx_RL);
//      Serial.print(", ");
//      Serial.print(Vx_FR);
//      Serial.print(", ");
//      Serial.println(Vx_RR);

      double Vy_FL = abs(sin(servoFL_Delta) * Vfl);
      double Vy_RL = abs(sin(servoRL_Delta) * Vrl);
      double Vy_FR = abs(sin(servoFR_Delta) * Vfr);
      double Vy_RR = abs(sin(servoRR_Delta) * Vrr);

      Vxf_Sum = Vx_FL+Vx_FR;
      Vxr_Sum = Vx_RL+Vx_RR;
      
      Vyf_Sum = Vy_FL+Vy_FR;
      Vyr_Sum = Vy_RL+Vy_RR;

      
      Vx_Sum = (Vxf_Sum+Vxr_Sum);
      Vy_Sum = (Vyf_Sum+Vyf_Sum);
        
      if(Avg_Count > 0)
      {
               
                  
                  double linearXVelocity = 0;
                  double linearYVelocity = 0;
                
                  double delta_x = 0;
                  double delta_y = 0;

                  long V_LinearX = 0;
                  long V_LinearY = 0;
                  
                  switch(MDIR)
                  {
                    case MDIR_MOVE_UP:
                    {
                      double V_YAW = Yaw;
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);
                    
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break;  
                    case MDIR_MOVE_DOWN:
                    {
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);

                      linearXVelocity = linearXVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break;  
                    case MDIR_TURN_CLOCKWISE:
                    linearXVelocity = 0;
                    linearYVelocity = 0;
                    break;  
                    case MDIR_TURN_ANTICLOCKWISE:
                    linearXVelocity = 0;
                    linearYVelocity = 0;
                    break;    
                    case MDIR_AKR_STEER_Q1:
                    {
//                       Serial.print("AKR_Q1:");
//                      Serial.print(Vxr_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);

                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vxr_Sum / Avg_Steer_Count);
                      linearYVelocity = (Vyr_Sum / Avg_Steer_Count);

                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break;
                    case MDIR_AKR_STEER_Q2:
                     {
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vxr_Sum / Avg_Steer_Count);
                      linearYVelocity = (Vyr_Sum / Avg_Steer_Count);
//                       Serial.print("AKR_Q2:");
//                      Serial.print(Vxr_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);

                      linearYVelocity = linearYVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break; 
                    case MDIR_AKR_STEER_Q3:
                     {
//                       Serial.print("AKR_Q3:");
//                      Serial.print(Vxr_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vxf_Sum / Avg_Steer_Count);
                      linearYVelocity = (Vyf_Sum / Avg_Steer_Count);

                      linearXVelocity = linearXVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break; 
                    case MDIR_AKR_STEER_Q4:
                     {
//                       Serial.print("AKR_Q4:");
//                      Serial.print(Vxf_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vxf_Sum / Avg_Steer_Count);
                      linearYVelocity = (Vyf_Sum / Avg_Steer_Count);

                      linearXVelocity = linearXVelocity * -1;
                      linearYVelocity = linearYVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break;
                    case MDIR_STEER_Q1:
                    {
//                       Serial.print("Q1:");
//                      Serial.print(Vx_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);

                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);

                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break; 
                    case MDIR_STEER_Q2:
                     {
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);
//                       Serial.print("Q2:");
//                      Serial.print(Vx_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);

                      linearYVelocity = linearYVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break; 
                    case MDIR_STEER_Q3:
                     {
//                       Serial.print("Q3:");
//                      Serial.print(Vx_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);

                      linearXVelocity = linearXVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break; 
                    case MDIR_STEER_Q4:
                     {
//                       Serial.print("Q4:");
//                      Serial.print(Vx_Sum);
//                      Serial.print(", ");
//                      Serial.println(linearXVelocity);
                      double V_YAW = Yaw;
                      
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);

                      linearXVelocity = linearXVelocity * -1;
                      linearYVelocity = linearYVelocity * -1;
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;
    
                      V_LinearX = linearXVelocity * 1000;
                      V_LinearY = linearYVelocity * 1000;
                      
                      X += delta_x;
                      Y += delta_y;
                    }
                    break;
                    case MDIR_MOVE_RIGHT:
                    {
                      double V_YAW = Yaw;
                       linearXVelocity = (Vx_Sum / Avg_Count);
                       linearYVelocity = (Vy_Sum / Avg_Count);

                       if(V_YAW < 0)
                      {
                       linearXVelocity = linearXVelocity * -1;
                      }
                      
                       linearYVelocity = linearYVelocity * -1;

                       
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;

                     
                        
                       V_LinearY = linearYVelocity * 1000;
                       
                       X += delta_x;
                       Y += delta_y;
                    }
                    break;
                    case MDIR_MOVE_LEFT:
                    {
                      double V_YAW = Yaw;
                      linearXVelocity = (Vx_Sum / Avg_Count);
                      linearYVelocity = (Vy_Sum / Avg_Count);

                       if(V_YAW > 0)
                      {
                       linearXVelocity = linearXVelocity * -1;
                      }
                      
                      
                      delta_x = (linearXVelocity * cos(V_YAW) - linearYVelocity * sin(V_YAW)) * diffSec;
                      delta_y = (linearXVelocity * sin(V_YAW) + linearYVelocity * cos(V_YAW)) * diffSec;

                        
                       V_LinearY = linearYVelocity * 1000;
                      
                      
                       X += delta_x;
                       Y += delta_y;
                    }
                    break;
                  }

  

          

                Write_ODOMeasure(COMMS_ODO_REG_BANK_X, X, Y, V_LinearX, V_LinearY,YawInfo, AngVelInfo );
                
//                Serial.print("MDIR : ");
//                Serial.println(MDIR, DEC);
//                Serial.print("X : ");
//                Serial.println(X, DEC);
//                Serial.print("Y : ");
//                Serial.println(Y, DEC);
//                Serial.print("V_LinearX : ");
//                Serial.println(V_LinearX, DEC);
//                Serial.print("V_LinearY : ");
//                Serial.println(V_LinearY, DEC);
//                Serial.print("YawInfo : ");
//                Serial.println(Yaw, DEC);
//                Serial.print("AngVelInfo : ");
//                Serial.println(AngVelInfo, DEC);
      }

}
}


void SetRequiredSpeed(int DEV_ADDRESS, int REG_ADDRESS, int LENGTH ,struct ODO_DATA* ODO_REF)
{
    uint16_t Current_PWM = ReadFromWire(DEV_ADDRESS, REG_ADDRESS, LENGTH);
    ODO_REF->CurrentPWM = (double)Current_PWM;
    if(Current_PWM != 65535 && ODO_REF->Velocity < 420)
    {
            
//        double gap = abs(ODO_REF->Velocity-ODO_REF->RequestedVelocity); //distance away from setpoint
//        if (gap < 10)
//        {
//          ODO_REF->SPEED_CNTRL->SetTunings(ODO_REF->consKp, ODO_REF->consKi, ODO_REF->consKd);
//        }
//        else
//        {
//          ODO_REF->SPEED_CNTRL->SetTunings(ODO_REF->aggKp, ODO_REF->aggKi, ODO_REF->aggKd);
//        }
//
//          ODO_REF->SPEED_CNTRL->Compute();

     int factor = 10;
     double gap = abs(ODO_REF->Velocity-ODO_REF->RequestedVelocity);
     if(gap > 30) factor = 200;
     if(gap > 25) factor = 150;
     if(gap > 20) factor = 100;
     if(gap > 10) factor = 30;
     else factor = 1;
   
      if(ODO_REF->Velocity > ODO_REF->RequestedVelocity && Current_PWM > factor) 
        Current_PWM = Current_PWM - factor;
        
      if(ODO_REF->Velocity < ODO_REF->RequestedVelocity && (Current_PWM + factor) < 60000) 
        Current_PWM = Current_PWM + factor;

    //  Current_PWM = ODO_REF->TargetPWM;
        
      byte UPDATED_PWM[2] = {((Current_PWM >> 8) & 0xFF), (Current_PWM & 0xFF)}; 
      WriteToWire(DEV_ADDRESS, REG_ADDRESS, LENGTH, UPDATED_PWM);
    }
}

void AdjustSpeed()
{
   if(ODO_FL.RequestedVelocity > 0)
   SetRequiredSpeed(WHL_CON_ADD, REG_PWM_FL, REG_PWM_LEN, &ODO_FL);
   
   if(ODO_RL.RequestedVelocity > 0)
   SetRequiredSpeed(WHL_CON_ADD, REG_PWM_RL, REG_PWM_LEN, &ODO_RL);
   
   if(ODO_FR.RequestedVelocity > 0)
   SetRequiredSpeed(WHL_CON_ADD, REG_PWM_FR, REG_PWM_LEN, &ODO_FR);
   
   if(ODO_RR.RequestedVelocity > 0)
   SetRequiredSpeed(WHL_CON_ADD, REG_PWM_RR, REG_PWM_LEN, &ODO_RR);
}

void ReadRequiredSpeed()
{
    uint16_t REG_Velocity = ReadFromWire(WHL_CON_ADD, REG_VEL_FL, REG_VEL_LEN);
    
    if(REG_Velocity < 420)
    {
      ODO_FL.RequestedVelocity = REG_Velocity;
      ODO_FL.SetVelocity = (double)ODO_FL.RequestedVelocity;
    }

    REG_Velocity = ReadFromWire(WHL_CON_ADD, REG_VEL_RL, REG_VEL_LEN);
    if(REG_Velocity < 420)
    {
      ODO_RL.RequestedVelocity = REG_Velocity;
      ODO_RL.SetVelocity = (double)ODO_RL.RequestedVelocity;
    }
    
    REG_Velocity = ReadFromWire(WHL_CON_ADD, REG_VEL_FR, REG_VEL_LEN);
    if(REG_Velocity < 420)
    {
      ODO_FR.RequestedVelocity = REG_Velocity;
      ODO_FR.SetVelocity = (double)ODO_FR.RequestedVelocity;
    }
    
    REG_Velocity = ReadFromWire(WHL_CON_ADD, REG_VEL_RR, REG_VEL_LEN);
    if(REG_Velocity < 420)
    {
      ODO_RR.RequestedVelocity = REG_Velocity;
      ODO_RR.SetVelocity = (double)ODO_RR.RequestedVelocity;
    }
}
