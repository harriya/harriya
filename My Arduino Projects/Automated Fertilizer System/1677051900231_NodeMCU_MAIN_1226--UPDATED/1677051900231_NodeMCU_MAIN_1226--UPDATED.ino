// #define BLYNK_TEMPLATE_ID "TMPLNhw6LWYn"
// #define BLYNK_DEVICE_NAME "Quickstart Template"
// #define BLYNK_AUTH_TOKEN "iPk0I_TiCTPUxzdpUVDFkM9b6_5MMuHn"

// #define BLYNK_TEMPLATE_ID "TMPLTi4Jans-"
// #define BLYNK_TEMPLATE_NAME "Automated Fertilizer System"
// #define BLYNK_AUTH_TOKEN "NF2cdF6k5sthVVMA8vA9-PlTsdTHVblG"
#define BLYNK_TEMPLATE_ID "TMPL1gbRHQy0"
#define BLYNK_TEMPLATE_NAME "Smart Fertilizer new"
#define BLYNK_AUTH_TOKEN "aRXlK1RUoTf3KCyK7M05q_02j30ZLpKN"


#define BLYNK_PRINT Serial
#include <DHT.h>
#include <SoilSensor.h>
#include <OneWire.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Shamila";
char pass[] = "aaaaaaaa";

int Vsensor1 = D1;
int Vsensor2 = D2;
float correctionfactor = 8;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000;
float R2 = 7500;
int value = 0;

void myTimerEvent()
{
  Blynk.virtualWrite(V8, millis()/ 100);
  Blynk.virtualWrite(V9, millis()/ 100);
}
BlynkTimer timer;

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Blynk.virtualWrite(V4, t);
 Blynk.virtualWrite(V2, h);
}

BLYNK_WRITE(V0){
  int value = param.asInt();
  value ? digitalWrite(D0, HIGH) : digitalWrite(D0, LOW);
  }
BLYNK_WRITE(V5){
  int value = param.asInt();
  value ? digitalWrite(D5, HIGH) : digitalWrite(D5, LOW);
  Serial.println(value);
    // if(value==1){
    //   digitalWrite(D5, HIGH);
    //   Serial.println("Valve 1 ON");
    // }else{
    //   digitalWrite(D5, LOW);
    //   Serial.println("Valve 1 OFF");
    // }
  }
  BLYNK_WRITE(V6){
  int value = param.asInt();
  value ? digitalWrite(D6, HIGH) : digitalWrite(D6, LOW);
  }
  BLYNK_WRITE(V7){
  int value = param.asInt();
  value ? digitalWrite(D7, HIGH) : digitalWrite(D7, LOW);
  }
  BLYNK_WRITE(V10){
  int value = param.asInt();
  value ? digitalWrite(1, HIGH) : digitalWrite(1, LOW);
  }
   BLYNK_WRITE(V11){
  int value = param.asInt();
  value ? digitalWrite(3, HIGH) : digitalWrite(3, LOW);
   }
void setup(){

  Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
   Serial.println("Serial started");

 pinMode(A0, INPUT);
 pinMode(D0, OUTPUT);  //relay
 pinMode(D5, OUTPUT);  //motor1
 pinMode(D6, OUTPUT);
 pinMode(D7, OUTPUT);
 pinMode(1, FUNCTION_3);
 pinMode(3, FUNCTION_3);
 pinMode(1, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(Vsensor1, INPUT);
 pinMode(Vsensor2, INPUT);
  dht.begin();
  timer.setInterval(100L, sendSensor);

}
int sensor=0;
int output=0;

void sendTemps()
{
 int sensor=analogRead(A0);
  output=(100-map(sensor,0,1023,0,100));
  Blynk.virtualWrite(V3,output); 
}
void Vsensor1value(){
  int sdata = 0;
  value = digitalRead(Vsensor1);
  vout = (value *5.0) / 1023.0;
  vin = vout / (R1/(R1+R2));

  vin = vin - correctionfactor;
  sdata = vin;
  Blynk.virtualWrite(V8, sdata);
}
void Vsensor2value(){
  int sdata = 0;
  value = digitalRead(Vsensor2);
  vout = (value * 5.0) / 1023.0;
  vin = vout / (R1/(R1+R2));

  vin = vin - correctionfactor;
  sdata = vin;
  Blynk.virtualWrite(V9, sdata);
}
void loop() {
 
  Blynk.run();
  timer.run();
  sendTemps();
}
