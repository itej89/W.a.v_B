

#define PIN_CPU_SWITCH 10

void setup() {
  // put your setup code here, to run once:
pinMode(PIN_CPU_SWITCH, OUTPUT);
digitalWrite(PIN_CPU_SWITCH, LOW);

delay(2000);
digitalWrite(PIN_CPU_SWITCH, HIGH);
delay(600);
digitalWrite(PIN_CPU_SWITCH, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
                      
}
