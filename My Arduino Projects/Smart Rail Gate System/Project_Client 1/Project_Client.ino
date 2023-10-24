#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
Servo servo;
const int gr1 = D2;
const int re1 = D3;

const char* ssid = "GG";
const char* password = "GG123456";

const char* serverGate = "http://192.168.4.1/gate";

String Gate;

unsigned long previousMillis = 0;
const long interval = 5000; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  servo.attach(D1);
  servo.write(0);
  digitalWrite (gr1, HIGH);
  delay(1000);
  digitalWrite(re1, HIGH);
  delay(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      Gate = httpGETRequest(serverGate);
      Serial.println(Gate);
      if (Gate == "1"){
        servo.write(180);
        delay(6000);
       servo.write(0);
       delay(1000);
      }

    }else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
