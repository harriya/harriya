
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char ssid[] = "HUAWEI-6101"; 
char pass[] = "40512077";
int flag=0;


void notifyOnFire()
{
  int isButtonPressed = digitalRead(D5);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("MOTION DETECTED");
    Blynk.notify("Alert : MOTION DETECTED!!!");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }

 
  
}
void setup()
{
Serial.begin(9600);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
pinMode(D5,INPUT_PULLUP);
timer.setInterval(5L,notifyOnFire); 
}



void loop()
{
  Blynk.run();
  timer.run();
}
