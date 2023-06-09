
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */




enum TOGGLE_SWITCH_STATES {SINGLE_PRESS, DOUBLE_PRESS, LONG_PRESS, BUTTON_OPEN} POWER_SWITCH_STATE = BUTTON_OPEN, ATTENTION_SWITCH_STATE = BUTTON_OPEN;

bool IsPowerButtonPressed = false;
boolean ISHandlingEvent = false;
boolean IsPowerOn = false;

#define POWER_SWITCH_PIN 2
#define  POWER_LATCH_PIN 13
#define  POWER2_LATCH_PIN 12
#define  POWER3_LATCH_PIN 11
#define  POWER4_LATCH_PIN 10

#define  POWER_SWITCH_LED 4

void PerformDeviceOnSteps()
{

  Serial.begin(115200);
  digitalWrite(POWER_LATCH_PIN, HIGH);
  digitalWrite(POWER2_LATCH_PIN, HIGH);
  digitalWrite(POWER3_LATCH_PIN, HIGH);
  digitalWrite(POWER4_LATCH_PIN, HIGH);
  digitalWrite(POWER_SWITCH_LED, HIGH);
  POWER_SWITCH_STATE = BUTTON_OPEN;

}

char ControllerStatus = 0;

void SHUT_DOWN()
{
  ControllerStatus = 3;
  Serial.end();
  detachInterrupt(0);
  digitalWrite(POWER_LATCH_PIN, LOW);
  digitalWrite(POWER2_LATCH_PIN, LOW);
  digitalWrite(POWER3_LATCH_PIN, LOW);
  digitalWrite(POWER4_LATCH_PIN, LOW);
  digitalWrite(POWER_SWITCH_LED, LOW);
  
  IsPowerOn = false;
}



void PowerSwitchInterrupt() // handle pin change interrupt for D0 to D7 here
 {
  if (IsPowerOn && !ISHandlingEvent && POWER_SWITCH_STATE == BUTTON_OPEN) {

    ISHandlingEvent = true;
    if (digitalRead(POWER_SWITCH_PIN) == LOW)
    {
      delay(50);
      if (digitalRead(POWER_SWITCH_PIN) == LOW)
      {

        int i = 0;

        while (digitalRead(POWER_SWITCH_PIN) == LOW)
        {

          delay(1);
          i++;
        }


        POWER_SWITCH_STATE = SINGLE_PRESS;

        if (i >= 1000) {
          
          POWER_SWITCH_STATE = LONG_PRESS;
        }
        else
        {
          int i = 0;
          while (digitalRead(POWER_SWITCH_PIN) == HIGH && i < 600)
          {
            delay(1);
            i++;
          }

          if (i < 600)
          {
            delay(100);
            if (digitalRead(POWER_SWITCH_PIN) == LOW)
            {
              int i = 0;

              while (digitalRead(POWER_SWITCH_PIN) == LOW)
              {

                delay(1);
                i++;
              }


              if (i <= 1000) {
                POWER_SWITCH_STATE = DOUBLE_PRESS;
              }
            }
          }
          {
          }

        }


      }
    }
  }
  ISHandlingEvent  = false;
 }  

void setup() {
  
  pinMode(2, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(POWER_SWITCH_LED, OUTPUT);
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW); 
  digitalWrite(11, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(POWER_SWITCH_LED, LOW);

  analogRead(A3);
  analogRead(A2);
  analogRead(A1);
  analogRead(A0);
  
   if (digitalRead(POWER_SWITCH_PIN) == LOW)
  {

     int i=0;
        while (digitalRead(POWER_SWITCH_PIN) == LOW)
        {
          delay(1);
          i++;
         if(i == 100){
              IsPowerOn = true;
              PerformDeviceOnSteps();
          }
          if(i==110) i=109;
        }

        if(i>=100)
        { 
          attachInterrupt(0, PowerSwitchInterrupt, FALLING);
        }
  }
}

int SecondCounter = 0;
int LowBatteryCount =0;
void loop() {

      if(SecondCounter >= 100)
      {
        float MotionCELL  = (analogRead(A3) * (5.21/1024.0) * (420.0/100.0))+(0.21); //Conversion+Diode Drop+Correction factor
        float HandCELL = (analogRead(A2) * (5.21/1024.0) * (420.0/100.0))+(0.33);
        float SensorCELL = (analogRead(A1) * (5.21/1024.0) * (420.0/100.0))+(0.33);
        float ComputeCELL = (analogRead(A0) * (5.21/1024.0) * (420.0/100.0))+(0.33);

        
//        float ComputeCELL = (analogRead(A0) * (5.21/1024.0) * (420.0/100.0))+(0.17);

        Serial.print("MotionCELL");
        Serial.println(MotionCELL);
        Serial.print("HandCELL");
        Serial.println(HandCELL);
        Serial.print("SensorCELL");
        Serial.println(SensorCELL);
        Serial.print("ComputeCELL");
        Serial.println(ComputeCELL);
        if(MotionCELL < 15 || SensorCELL < 15 || ComputeCELL < 15)
        {
          LowBatteryCount++;
          if(LowBatteryCount > 500)
          {
            SHUT_DOWN();
          }
        }
        else
        {
          LowBatteryCount = 0;
        }
        SecondCounter = 0;
      }
      
         if(POWER_SWITCH_STATE == SINGLE_PRESS || POWER_SWITCH_STATE == DOUBLE_PRESS )
          {
            POWER_SWITCH_STATE = BUTTON_OPEN;
          }
        else
         if(POWER_SWITCH_STATE == LONG_PRESS)
          {
            SHUT_DOWN();
          }
   

   delay(10);
   SecondCounter++;

}
