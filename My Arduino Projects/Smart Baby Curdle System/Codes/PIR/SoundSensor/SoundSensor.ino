//Viral Science www.youtube.com/c/viralscience
//Blynk Fire Alarm Notification
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "7ZyWCVN9OUre-S4zhWhzdmcsevVK6Urz"; //Auth code sent via Email
char ssid[] = "POCO X3 NFC"; //Wifi name
char pass[] = "12345678";  //Wifi Password
int flag=0;
void notifyOnFire()
{
  int isButtonPressed = digitalRead(D1);
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
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);
timer.setInterval(5L,notifyOnFire); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
