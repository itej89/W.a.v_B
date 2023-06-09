#include <Servo.h>
#include <Wire.h>


int16_t HR_CALIB[180] = { 525, 521, 519, 516, 514, 514, 510, 508, 505, 503,  
                          501, 498, 497, 494, 491, 490, 487, 485, 483, 480, 
                          478, 476, 473, 471, 469, 466, 464, 462, 459, 457, 
                          455, 453, 450, 449, 445, 444, 441, 439, 437, 435, 
                          432, 431, 429, 425, 424, 421, 419, 417, 414, 412, 
                          410, 408, 405, 403, 401, 398, 396, 393, 392, 390, 
                          387, 385, 382, 380, 378, 375, 373, 371, 368, 367, 
                          364, 362, 360, 357, 355, 353, 351, 348, 347, 344, 
                          341, 339, 337, 335, 333, 329, 327, 326, 323, 322, 
                          322, 318, 317, 314, 312, 309, 307, 305, 303, 301, 
                          298, 295, 294, 291, 288, 286, 284, 281, 279, 278, 
                          275, 274, 271, 268, 265, 263, 261, 259, 257, 255, 
                          252, 249, 247, 245, 243, 241, 239, 236, 233, 231, 
                          229, 226, 224, 222, 220, 217, 215, 213, 210, 208, 
                          207, 203, 201, 200, 196, 194, 192, 190, 188, 185, 
                          183, 180, 178, 176, 174, 171, 168, 166, 163, 161, 
                          159, 156, 154, 152, 149, 146, 144, 142, 139, 137, 
                          134, 132, 129, 129, 129, 128, 128, 128, 128, 128 }; 

int16_t HP_CALIB[180] = { 126, 126, 127, 127, 128, 129, 130, 131, 132, 134, 
                          138, 137, 140, 143, 146, 148, 150, 152, 155, 157, 
                          160, 162, 166, 167, 171, 172, 174, 177, 179, 182, 
                          184, 186, 188, 191, 194, 195, 199, 200, 203, 205, 
                          209, 210, 212, 215, 217, 220, 222, 225, 226, 229,
                          231, 234, 236, 238, 240, 242, 245, 248, 250, 252, 
                          256, 257, 258, 262, 263, 267, 269, 271, 274, 276, 
                          278, 280, 282, 286, 287, 289, 292, 294, 297, 299, 
                          301, 304, 306, 308, 311, 312, 315, 318, 320, 322, 
                          323, 325, 326, 330, 332, 334, 336, 338, 342, 344, 
                          345, 347, 350, 352, 355, 357, 360, 361, 364, 367, 
                          368, 371, 373, 376, 378, 380, 382, 385, 388, 390, 
                          391, 394, 396, 399, 402, 404, 407, 408, 410, 413, 
                          415, 417, 420, 423, 424, 427, 429, 431, 433, 435, 
                          438, 440, 442, 445, 447, 449, 452, 454, 457, 458, 
                          462, 463, 465, 468, 470, 473, 474, 477, 479, 482, 
                          483, 486, 488, 491, 493, 496, 498, 499, 502, 504, 
                          506, 510, 512, 515, 516, 518, 521, 522, 525, 527 }; 

#define SERVO_MIN_US 771
#define SERVO_MAX_US 2740

#define SERVO_MIN_DEG 0
#define SERVO_MAX_DEG 180

#define HR_PWM 10
#define HP_PWM 11

int servoHR_Angle = 0xFF;  
int servoHP_Angle = 0xFF;  


int servoHR_Now_Angle = 90;  
int servoHP_Now_Angle = 90;  


double servoHR_CALIB = 0x5A;  
double servoHP_CALIB = 0x5A;  


struct ServoAttach
{
  uint8_t ServoHR : 1;
  uint8_t ServoHP : 1;
}Status;

Servo servoHR;
Servo servoHP;

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
//        
//          I2cRegBank[Address+i]  = Wire.read();
//       }
  }
}




void setup() {

    Wire.begin(12);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    
    Serial.begin(115200);

    
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    Status.ServoHR = 0;
    Status.ServoHP = 0;
}

void loop() {
  delay(10);
  serialRead();

  if(ShouldSendStatus)
  {
    ShouldSendStatus = false;
     if(servoHR_Angle != servoHR_Now_Angle || 
        servoHP_Angle != servoHP_Now_Angle )
        {

          int HR_Sign = servoHR_Now_Angle > servoHR_Angle? -1 : 1;
          int HP_Sign = servoHP_Now_Angle > servoHP_Angle? -1 : 1;

          while(servoHR_Angle != servoHR_Now_Angle || 
                servoHP_Angle != servoHP_Now_Angle )
          {
            if(!ShouldSendStatus)
            {
              if(servoHR_Now_Angle != servoHR_Angle)
              {
                servoHR_Now_Angle += (HR_Sign * 1);
                
                servoHR.write(servoHR_Now_Angle);
              }
              
              delay(10);
              if(servoHP_Now_Angle != servoHP_Angle)
              {
                servoHP_Now_Angle += (HP_Sign * 1);
                
                servoHP.write(servoHP_Now_Angle);
              }
              delay(10);
            }
            else
            {
               break;  
            }
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
byte c[8];
void serialRead() {

   
   while (Serial.available()) {
    while(Serial.available())
    {
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
    }

    
  if(c[0] == 'S' && c[1] == 'S' && c[6] == 'S' && c[7] == 'P')
  {
      ShouldSendStatus = true;
      uint16_t  servoHR_Info =  ((c[2] << 8)|c[3]);
      uint16_t  servoHP_Info =  ((c[4] << 8)|c[5]);


      //remove direction bits, add decimal point by scalling by 10000 and convert to degrees 
      double  _servoHR_Delta =  ExtractDeltaDegree(servoHR_Info);
      double  _servoHP_Delta =  ExtractDeltaDegree(servoHP_Info);

      int   servoHR_DIR = ExtractDirection(servoHR_Info);
      int   servoHP_DIR = ExtractDirection(servoHP_Info);


            //substract for right turn
      double _servoHR_Delay = servoHR_CALIB +  (-1 * servoHR_DIR * _servoHR_Delta);
      if(servoHR_DIR == 0xFF)
      {
         servoHR_Angle = 0xFF;
         servoHR_Now_Angle = 0xFF;
         
        if(Status.ServoHR == 1)
        {
           servoHR.detach();
           Status.ServoHR = 0;
        }
      }
      else 
      {  
         servoHR_Angle = _servoHR_Delay;
         
        if(Status.ServoHR == 0)
        {
            Status.ServoHR = 1; 
             int turn = analogRead(A0);
            int index = 0;
            for(int i=0; i<180; i++)
            {
              if(HR_CALIB[i] > turn)
              {
                index++;
              }
              else
              {
                  break;
              }
            }
            
            
            servoHR.write(index); 
            delay(500);
            servoHR.attach(HR_PWM); 
            servoHR_Now_Angle = index;

            
        }
      }



          //substract for right turn
      double _servoHP_Delay = servoHP_CALIB +  (-1 * servoHP_DIR * _servoHP_Delta);
      if(servoHP_DIR == 0xFF)
      {
         servoHP_Angle = 0xFF;
         servoHP_Now_Angle = 0xFF;
         
        if(Status.ServoHP == 1)
        {
           servoHP.detach();
           Status.ServoHP = 0;
        }
      }
      else 
      {  
         servoHP_Angle = _servoHP_Delay;
         
        if(Status.ServoHP == 0)
        {
            Status.ServoHP = 1; 
             int turn = analogRead(A1);
            int index = 0;
            for(int i=0; i<180; i++)
            {
              if(HP_CALIB[i] < turn)
              {
                index++;
              }
              else
              {
                  break;
              }
            }
            
            
            servoHP.write(index); 
            delay(500);
            servoHP.attach(HP_PWM); 
            servoHP_Now_Angle = index;

            
        }
      }







      
      
      for(int i=0; i<8; i++)
      {c[i] = '\0';}
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
