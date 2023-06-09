
#define CELL_COUNT 4

int Relay_Pins[CELL_COUNT] = {10,15,14,16};

int CellNumber = 0;

void setupContext()
{
  CellNumber = 0;
}

void startCharging()
{
  if(CellNumber < CELL_COUNT)
  {
    //Turn Off the Relay of current cell
    if(CellNumber > 0)
    {
      digitalWrite(Relay_Pins[CellNumber-1], HIGH);
    }

    //Turn on the Relay of next cell
    digitalWrite(Relay_Pins[CellNumber++], LOW);

    delay(2000);
  }
  else
  {
     if(CellNumber > 0)
    {
      digitalWrite(Relay_Pins[CellNumber-1], HIGH);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(10, OUTPUT);
pinMode(15, OUTPUT);
pinMode(14, OUTPUT);
pinMode(16, OUTPUT);

digitalWrite(10, HIGH);
digitalWrite(15, HIGH);
digitalWrite(14, HIGH);
digitalWrite(16, HIGH);

setupContext();

}

void loop() {
  
  //Check if Charging is finished
  if(analogRead(A1) > 3*(1023/5))
  {
    startCharging();  
  }

  delay(2000);
  
}
