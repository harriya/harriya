

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "7ZyWCVN9OUre-S4zhWhzdmcsevVK6Urz";
char ssid[] = "POCO X3 NFC";
char pass[] = "12345678";
int flag=0;



void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(D3);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("CRYING");
    Blynk.notify("Alert : Your Baby is Crying!!!");
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
pinMode(D3,INPUT_PULLUP);
timer.setInterval(5L,notifyOnButtonPress); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
