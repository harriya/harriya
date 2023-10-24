


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "7ZyWCVN9OUre-S4zhWhzdmcsevVK6Urz";

char ssid[] = "POCO X3 NFC";
char pass[] = "12345678";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
