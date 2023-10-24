#define BLYNK_TEMPLATE_ID "TMPL84lh55xb"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "NLDBqXmMeSFLGolH6DAnAhmH71ZH8UFT"

#define BLYNK_PRINT Serial 
#include <DHT.h>  
#include <SPI.h>
#include <ESP8266WiFi.h>       
#include <BlynkSimpleEsp8266.h>
//#include <SimpleTimer.h>



char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Shamila";
char pass[] = "aaaaaaaa"; 
int flag=0;  

/* DHT11*/
#include <DHT.h>
BlynkTimer timer;
#define DHTPIN D5 // DHT 11 : Temperature & humidity sensor connected to digital pin D0
#define DHTTYPE DHT11 // Sensor type : DHT11
DHT dht(DHTPIN, DHTTYPE); // Send DHT pin and type parameter to DHT Function 
float hum = 0; /* at init humidity is 0 */
float temp = 0;/* at init temp is 0*/

// #define DHTPIN D2         

// #define DHTTYPE DHT11     // DHT 11


// DHT dht(DHTPIN, DHTTYPE);



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

// Pin connected to the fan
const int fanPin = D1;
 
  


// void notifyOnButtonPress()
// {
//   int isButtonPressed = digitalRead(D3);
//   if (isButtonPressed==1 && flag==0) {
//     Serial.println("CRYING");
//     Blynk.notify("Alert : Your Baby is Crying!!!");
//     flag=1;
//   }
//   else if (isButtonPressed==0)
//   {
//     flag=0;
//   }
// }



void setup()
{  

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
  timer.setInterval(1000L, sendSensor);
   pinMode(A0, INPUT);

//   Serial.begin(9600);
// Blynk.begin(auth, ssid, pass);
// pinMode(D3,INPUT_PULLUP);
// timer.setInterval(5L,notifyOnButtonPress); 

// Serial.begin(9600);
// Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
// pinMode(D5,INPUT_PULLUP);
// timer.setInterval(5L,notifyOnFire); 
// 
pinMode(fanPin, OUTPUT);

}

void loop()
{

  
  Blynk.run(); 
  timer.run(); 
  // sendTemps();
}

BLYNK_WRITE(V1)
{
  int fanState = param.asInt();

  // Turn on/off the fan based on the Blynk app button state
  if (fanState == HIGH)
  {
    digitalWrite(fanPin, HIGH); // Turn on the fan
    Serial.println("Fan turned on");
  }
  else
  {
    digitalWrite(fanPin, LOW); // Turn off the fan
    Serial.println("Fan turned off");
  }
}
