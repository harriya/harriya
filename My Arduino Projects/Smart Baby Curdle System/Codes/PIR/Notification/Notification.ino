
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "PyzZmaKpP5pWIdRFaosanfDdaUNMKzjf";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HUAWEI-6101";
char pass[] = "40512077";

int sensor=D2;
int sensorval=0;
int OUT=0;

void setup()
{
  pinMode(D2,INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
 
    sensorval=digitalRead(D2);
 
       delay(1000);

       Blynk.virtualWrite(V0,OUT);
    Blynk.run();
 
  }
