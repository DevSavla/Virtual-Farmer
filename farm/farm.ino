#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS D2
#define pump1 D7
#define pump2 D8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
DHT dht;

const int moisture_pin = A0;

float cur_lat;
float cur_lon;
float soil_moisture;
float humidity_p;
float temperature_c;
float temperature_f;
float soil_temperature;

const char *ssid = "Dev";
const char *password = "qwertyuiop";`
const char *host = "http://192.168.43.48:8000/api/save-data/";

void setup() 
{  
    pinMode(pump1,OUTPUT);
    pinMode(pump2,OUTPUT);
    pinMode(moisture_pin,INPUT);
    
    dht.setup(D1);
    
    WiFi.begin(ssid, password);
  
    Serial.begin(9600);

    DS18B20.begin();
    
    while(WiFi.status() != WL_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }
  
    Serial.println("");

    Serial.print("Connected to ");
    Serial.println(ssid);
    
//    Serial.print("IP Address: ");
//    Serial.println(WiFi.localIP());
}

void loop() 
{
    cur_lat = 19.0968;
    cur_lon = 72.8517;

    humidity_p = dht.getHumidity();
    temperature_c = dht.getTemperature();

    soil_moisture = ( 100.00 - ( (analogRead(moisture_pin)/1023.00) * 100.00 ) );

    DS18B20.requestTemperatures(); 
    soil_temperature = DS18B20.getTempCByIndex(0);

    if(soil_moisture<40.00)
    {
      Serial.println("Loop");
      digitalWrite(pump1,HIGH);
      digitalWrite(pump2,HIGH);
      delay(10000);
      digitalWrite(pump1,LOW);
      digitalWrite(pump2,LOW);
    }

    else
    {
      digitalWrite(pump1,LOW);
      digitalWrite(pump2,LOW);
    }

    HTTPClient http;
    
    http.begin(host);
    
    String str_post = String("1")+String("$")+String(cur_lat)+String("$")+String(cur_lon)+String("$")+String(temperature_c)+String("$")+String(humidity_p)+String("$")+String(soil_moisture)+String("$")+String(soil_temperature)+String("$");
    int httpCode = http.POST(str_post);
    String payload = http.getString();

    http.end();

    delay(2000);
}
