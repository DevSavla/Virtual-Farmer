#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS D2 // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float soil_temperature;

void setup() 
{
  Serial.begin(9600);
  DS18B20.begin();
}

void loop() 
{
  DS18B20.requestTemperatures(); 
  soil_temperature = DS18B20.getTempCByIndex(0);
  Serial.println(soil_temperature);
}
