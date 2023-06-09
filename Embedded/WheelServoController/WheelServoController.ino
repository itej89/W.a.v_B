#include <Servo.h>
#include <Wire.h>

#define SERVO_MIN_US 771
#define SERVO_MAX_US 2740

#define SERVO_MIN_DEG 0
#define SERVO_MAX_DEG 180

#define FL_PWM 8
#define RL_PWM 3
#define FR_PWM 6
#define RR_PWM 4
 

//
//double servoFL_CALIB = 0x5C;  
//double servoFR_CALIB = 0x2D; 
//double servoRL_CALIB = 0x2A; 
//double servoRR_CALIB = 0x53;   


double servoFL_CALIB = 0x5C;  
double servoFR_CALIB = 0x2F; 
double servoRL_CALIB = 0x29; 
double servoRR_CALIB = 0x52;   


int servoFL_Angle = 0xFF;  
int servoFR_Angle = 0xFF; 
int servoRL_Angle = 0xFF; 
int servoRR_Angle = 0xFF;   


int servoFL_Now_Angle = 90;  
int servoFR_Now_Angle = 90; 
int servoRL_Now_Angle = 90; 
int servoRR_Now_Angle = 90;  


struct ServoAttach
{
  uint8_t ServoFL : 1;
  uint8_t ServoFR : 1;
  uint8_t ServoRL : 1;
  uint8_t ServoRR : 1;
}Status;

Servo servoFL;
Servo servoFR;
Servo servoRL;
Servo servoRR;

bool ShouldSendStatus = false;


//Protocol 1byte Address of regeister bank(Index), 1byte Data len, Data
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int Count) {
  
  while(Wire.available() > 0)
  {
       byte Address = Wire.read();
//       byte len = Wire.read();
//  
//       while(len > Wire.available());
//          
//       for(int i=0; i<len; i++)
//       {
//          I2cRegBank[Address+i]  = Wire.read();
//       }
  }
}




void setup() {

    Wire.begin(12);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    
    Serial.begin(115200);
    
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    Status.ServoFL = 0;
    Status.ServoFR = 0;
    Status.ServoRL = 0;
    Status.ServoRR = 0;
}

void loop() {
  delay(10);
  serialRead();
  if(ShouldSendStatus)
  {
          ShouldSendStatus = false;
    
          int i=0;
          while(i<180 && (servoFL_Angle != servoFL_Now_Angle || 
                servoRL_Angle != servoRL_Now_Angle ||
                servoFR_Angle != servoFR_Now_Angle ||
                servoRR_Angle != servoRR_Now_Angle))
          {

            if(Serial.available())
            {
              serialRead();
              if(ShouldSendStatus)
              {
                 i=0;
                 continue;
              }
            }
            i++;
            if(!ShouldSendStatus)
            {
              if(servoFL_Now_Angle != servoFL_Angle)
              {
                if(servoFL_Now_Angle > servoFL_Angle)servoFL_Now_Angle--;
                if(servoFL_Now_Angle < servoFL_Angle)servoFL_Now_Angle++;
                
                servoFL.write(180-servoFL_Now_Angle);
              }
              
              delay(10);
              if(servoRL_Now_Angle != servoRL_Angle)
              {
                if(servoRL_Now_Angle > servoRL_Angle)servoRL_Now_Angle--;
                if(servoRL_Now_Angle < servoRL_Angle)servoRL_Now_Angle++;
                
                servoRL.write(servoRL_Now_Angle);
              }
              delay(10);
              if(servoFR_Now_Angle != servoFR_Angle)
              {
                if(servoFR_Now_Angle > servoFR_Angle)servoFR_Now_Angle--;
                if(servoFR_Now_Angle < servoFR_Angle)servoFR_Now_Angle++;
                
                servoFR.write(servoFR_Now_Angle);
              } 
              delay(10);
              if(servoRR_Now_Angle != servoRR_Angle)
              {
                if(servoRR_Now_Angle > servoRR_Angle)servoRR_Now_Angle--;
                if(servoRR_Now_Angle < servoRR_Angle)servoRR_Now_Angle++;
                
                servoRR.write(servoRR_Now_Angle);
              }
              delay(10);
            }
            else
            {
               break;  
            }
          }
          
        

          if(!ShouldSendStatus)
          {
             delay(50);
            
            Serial.write(0xCC);  
          }
    
  }
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
   return (((double)(ServoInfo & 0x3FFF))/10000.0)*(180/PI);
}


int index = 0;
byte c[12];
void serialRead() {

   while (Serial.available()) {
    
    //while(Serial.available())
    //{
      byte inChar = (byte)Serial.read();
    
      if(inChar != '\0')
      {
        c[index++] = inChar;
      }
      else
      if(index > 1 && c[0] == 'S' && c[1] == 'S')
      {
         c[index++] = inChar;
      }
      else
        index = 0;
    //}

    
  if(index == 12 && (c[0] == 'S' && c[1] == 'S' && c[10] == 'S' && c[11] == 'P'))
  {

    index = 0;
   ShouldSendStatus = true;
   

      uint16_t  servoFL_Info =  ((c[2] << 8)|c[3]);
      uint16_t  servoRL_Info =  ((c[4] << 8)|c[5]);
      uint16_t  servoFR_Info =  ((c[6] << 8)|c[7]);
      uint16_t  servoRR_Info =  ((c[8] << 8)|c[9]);


      //remove direction bits, add decimal point by scalling by 10000 and convert to degrees 
      double  _servoFL_Delta =  ExtractDeltaDegree(servoFL_Info);
      double  _servoRL_Delta =  ExtractDeltaDegree(servoRL_Info);
      double  _servoFR_Delta =  ExtractDeltaDegree(servoFR_Info);
      double  _servoRR_Delta =  ExtractDeltaDegree(servoRR_Info);

      int   servoFL_DIR = ExtractDirection(servoFL_Info);
      int   servoRL_DIR = ExtractDirection(servoRL_Info);
      int   servoFR_DIR = ExtractDirection(servoFR_Info);
      int   servoRR_DIR = ExtractDirection(servoRR_Info);

//      Serial.print(servoFL_Info, HEX);
//      Serial.print(", ");
//      Serial.print(servoRL_Info, HEX);
//      Serial.print(", ");
//      Serial.print(servoFR_Info, HEX);
//      Serial.print(", ");
//      Serial.println(servoRR_Info, HEX);
//
//      
//      Serial.print(_servoFL_Delta);
//      Serial.print(", ");
//      Serial.print(_servoRL_Delta);
//      Serial.print(", ");
//      Serial.print(_servoFR_Delta);
//      Serial.print(", ");
//      Serial.println(_servoRR_Delta);
//      
//      Serial.print(servoFL_DIR);
//      Serial.print(", ");
//      Serial.print(servoRL_DIR);
//      Serial.print(", ");
//      Serial.print(servoFR_DIR);
//      Serial.print(", ");
//      Serial.println(servoRR_DIR);
     

      ///////heading///////
      //Servo1  -----   //Servo3
      //Servo2  -----   //servo4 
      ///////Backside/////

      //substract for right turn
      double _servoFL_Delay = servoFL_CALIB +  (-1 * servoFL_DIR * _servoFL_Delta);
      if(servoFL_DIR == 0xFF)
      {
         servoFL_Angle = 0xFF;
         servoFL_Now_Angle = 0xFF;
         
        if(Status.ServoFL == 1)
        {
           servoFL.detach();
           Status.ServoFL = 0;
        }
      }
      else 
      {  
         servoFL_Angle = _servoFL_Delay;
         
        if(Status.ServoFL == 0)
        {
            Status.ServoFL = 1;  
            servoFL.attach(FL_PWM, SERVO_MIN_US, SERVO_MAX_US);
            servoFL_Now_Angle = servoFL_Angle;
            servoFL.write(servoFL_Angle);
        }
      }


      //substract for right turn
      double _servoRL_Delay = servoRL_CALIB +  (-1 * servoRL_DIR * _servoRL_Delta);
      if(servoRL_DIR == 0xFF)
      {
        servoRL_Angle = 0xFF;
        servoRL_Now_Angle = 0xFF;
        if(Status.ServoRL == 1)
        {
           servoRL.detach();
           Status.ServoRL = 0;
        }
      }
      else
      {  
         servoRL_Angle = _servoRL_Delay;
         if(Status.ServoRL == 0)
        {
            Status.ServoRL = 1; 
            servoRL.attach(RL_PWM, SERVO_MIN_US, SERVO_MAX_US);
            servoRL_Now_Angle = servoRL_Angle;
            servoRL.write(servoRL_Angle); 
        }
      }


      double _servoFR_Delay = servoFR_CALIB +  (servoFR_DIR * _servoFR_Delta);
      if(servoFR_DIR == 0xFF)
      {
         servoFR_Angle = 0xFF;
         servoFR_Now_Angle = 0xFF;
        if(Status.ServoFR == 1)
        {
           servoFR.detach();
           Status.ServoFR = 0;
        }
      }
      else
      {   
        servoFR_Angle = _servoFR_Delay;
        
        if(Status.ServoFR == 0)
        {
            Status.ServoFR = 1; 
            servoFR.attach(FR_PWM, SERVO_MIN_US, SERVO_MAX_US);
            servoFR_Now_Angle = servoFR_Angle;
            servoFR.write(servoFR_Angle); 
        }
      }


      double _servoRR_Delay = servoRR_CALIB +  (-1*servoRR_DIR * _servoRR_Delta);
      if(servoRR_DIR == 0xFF)
      {
         servoRR_Angle = 0xFF;
         servoRR_Now_Angle = 0xFF;
         if(Status.ServoRR == 1)
         {
           servoRR.detach();
           Status.ServoRR = 0;
         }
      }
      else
      {
        servoRR_Angle = _servoRR_Delay;  
        
        if(Status.ServoRR == 0)
        {
            Status.ServoRR = 1;
            servoRR.attach(RR_PWM, SERVO_MIN_US, SERVO_MAX_US);  
            servoRR_Now_Angle = servoRR_Angle; 
            servoRR.write(servoRR_Angle); 
        }
      }


      for(int i=0; i<12; i++)
      {c[i] = '\0';}


            
      Serial.write(0xBB);  
      break;
  }

  }

}

int DegreeToServoDelay(double degree)
{
   return mapfloat(degree, SERVO_MIN_DEG, SERVO_MAX_DEG, SERVO_MIN_US, SERVO_MAX_US);
}


float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
