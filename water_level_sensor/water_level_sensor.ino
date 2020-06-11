#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int water_level=D5;
const int sensorMin = 0; 
const int sensorMax = 1024; 

const char *ssid = "Dev";
const char *password = "qwertyuiop";
const char *host = "http://192.168.43.48:8000/api/notify-tank/";

int notification_flag=0;

void setup() 
{
    Serial.begin(9600);
    pinMode(water_level,INPUT);

    WiFi.begin(ssid, password);
    
    while(WiFi.status() != WL_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }
  
    Serial.println("");

    Serial.print("Connected to ");
    Serial.println(ssid);
    
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    int sensorReading = digitalRead(water_level);
    Serial.println(sensorReading);

    if(sensorReading!=0)
    {
       Serial.println("Tank Full");
    }

    else
    {
      notification_flag=1;
      Serial.println("Tank Empty");
    }

    HTTPClient http;
    
    http.begin(host);
    
    String str_post = String(notification_flag);
    int httpCode = http.POST(str_post);
    String payload = http.getString();

    http.end();

    notification_flag=0;

    delay(2000); 
}
