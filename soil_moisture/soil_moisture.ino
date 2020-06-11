const int moisture_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

void setup() 
{
  pinMode(moisture_pin,INPUT);
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  float soil_moisture;

  soil_moisture = ( 100.00 - ( (analogRead(moisture_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture = ");
  Serial.print(soil_moisture);
  Serial.println("%");

  delay(2000);
}
