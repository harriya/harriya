// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const int ir_near = D1;  //close to gate 
const int ir_far = D2;  //far from gate
bool isGateOpen = false;

int val_near =0;
int val_far =0;

// Set your access point network credentials
const char* ssid = "GG";
const char* password = "GG123456";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readGate(){
  return String(isGateOpen);
}

void setup() {
  pinMode(ir_near,INPUT);
  pinMode(ir_far,INPUT);
  pinMode(D0, OUTPUT);
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

 
  // Setting the ESP as an access point
  Serial.print("Setting AP…");
  // // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/gate", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readGate().c_str());
  });
  bool status;

  // // default settings
  // // (you can also pass in a Wire library object like &Wire2)
  // status = bme.begin(0x76);  
  // if (!status) {
  //   Serial.println("Could not find a valid BME280 sensor, check wiring!");
  //   while (1);
  // }
  
  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // val_near = digitalRead(ir_near);
  // val_far = digitalRead(ir_far);
  // Serial.println(val_near);
  // Serial.println(val_far);
  digitalWrite(D0, HIGH);
  isGateOpen = false;
  
  if(digitalRead(ir_far) ==LOW){
    val_far = 1;
  }
  if(digitalRead(ir_near) ==LOW){
    val_near = 1;
  }

  while(val_far == 1 && val_near == 1){
     //if(val_near == 1 && val_far == 0 ){
      // isGateOpen = true;
      // Serial.println("Gate Close");
     //}
     //if(val_far == 1 && val_near == 0){
       //Serial.println("Gate Open");
       //isGateOpen = false;
    // }
    digitalWrite(D0, LOW);
    isGateOpen = true;
    Serial.println("Gate Close");
    delay(12000);
    Serial.println("Gate Open");
    val_far = 0;
    val_near = 0;
  }
  
}
