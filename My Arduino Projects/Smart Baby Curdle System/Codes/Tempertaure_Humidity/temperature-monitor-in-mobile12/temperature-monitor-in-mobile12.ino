
#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>       
#include <BlynkSimpleEsp8266.h>
//#include <SimpleTimer.h>
#include <DHT.h>


char auth[] = "7ZyWCVN9OUre-S4zhWhzdmcsevVK6Urz"; 
 
char ssid[] = "POCO X3 NFC"; 
char pass[] = "12345678";    

#define DHTPIN D2         

#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  
 
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V2, h);  //V1 is for Humidity
  Blynk.virtualWrite(V3, t);  //V0 is for Temperature
}

void setup()
{  

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); 
  timer.run(); 
}
