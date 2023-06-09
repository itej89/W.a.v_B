#include <PinChangeInt.h>

#define ENCODER_PIN_FL 2

long TickCount;

void Counter() {
  TickCount++;
}


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);

  pinMode(ENCODER_PIN_FL, INPUT); digitalWrite(ENCODER_PIN_FL, HIGH);
  PCintPort::attachInterrupt(ENCODER_PIN_FL, &Counter, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(TickCount);
 delay(1000);
}
