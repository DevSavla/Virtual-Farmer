#define pump D6

void setup() 
{
  pinMode(pump,OUTPUT);
  digitalWrite(pump,HIGH);
}

void loop() 
{
  digitalWrite(pump,HIGH);
}
