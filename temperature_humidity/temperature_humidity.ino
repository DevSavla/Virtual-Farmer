#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);
  dht.setup(D1);   /* D1 is used for data communication */
}

void loop()
{
  
  float humidity_p = dht.getHumidity();/* Get humidity value */
  float temperature_c = dht.getTemperature();/* Get temperature value */
  float temperature_f=dht.toFahrenheit(temperature_c);
  
  Serial.println(temperature_f, 1);/* Convert temperature to Fahrenheit units */
  delay(2000);
}
