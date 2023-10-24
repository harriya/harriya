#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
Servo servo;
const int red1 = D2;
const int red2 = D7;

const int green1 = D6;
const int green2 = D3;



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
  // digitalWrite(D2, HIGH);

  // digitalWrite(D6, HIGH);
  // delay(1000);
  // digitalWrite(D3, LOW);
  // digitalWrite(D7, LOW);
  // delay(1000);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);

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
        digitalWrite(green1,HIGH);
        digitalWrite(green2,HIGH);
        digitalWrite(red1,LOW);
        digitalWrite(red2,LOW);
        delay(500);
        
      }else{
        servo.write(0);
        digitalWrite(red1,HIGH);
        digitalWrite(red2,HIGH);
        digitalWrite(green1,LOW);
        digitalWrite(green2,LOW);
        delay(500);
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
