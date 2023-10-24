//Viral Science www.youtube.com/c/viralscience  www.viralsciencecreativity.com
//Blynk Door Security Notification System

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "7ZyWCVN9OUre-S4zhWhzdmcsevVK6Urz"; //Enter the authentication code sent by Blynk to your Email
char ssid[] = "POCO X3 NFC"; //Enter your WIFI SSID
char pass[] = "12345678"; //Enter your WIFI Password
int flag=0;



void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(D4);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("URINATES");
    Blynk.notify("Alert : Your baby has urinated!!!");
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
Blynk.begin(auth, ssid, pass);
pinMode(D4,INPUT_PULLUP);
timer.setInterval(5L,notifyOnButtonPress); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
