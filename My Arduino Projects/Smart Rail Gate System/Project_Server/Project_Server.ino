// Import required libraries
//#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const int ir_near1 = D1;  //close to gate 
const int ir_far1 = D2;  //far from gate
const int ir_near2 = D3;
const int ir_far2 = D4;

bool isGateOpen = false;

int val_near1 =0;
int val_far1 =0;
int val_near2 =0;
int val_far2 =0;

// Set your access point network credentials
const char* ssid = "GG";
const char* password = "GG123456";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readGate(){
  return String(isGateOpen);
}

void setup() {
  pinMode(ir_near1,INPUT);
  pinMode(ir_far1,INPUT);
  pinMode(ir_near2,INPUT);
  pinMode(ir_far2,INPUT);
  
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
  
  if(digitalRead(ir_far1) ==LOW){
    val_far1 = 1;
  }
  if(digitalRead(ir_near1) ==LOW){
    val_near1 = 1;
  }
  if(digitalRead(ir_far2) ==LOW){
    val_far2 = 1;
  }
  if(digitalRead(ir_near2) ==LOW){
    val_near2 = 1;
  }
  Serial.print("Far 1 = ");
  Serial.println(val_far1);
  Serial.print("Near 1 = ");
  Serial.println(val_near1);
  Serial.print("Far 2 = ");
  Serial.println(val_far2);
  Serial.print("Near 2 = ");
  Serial.println(val_near2);
  delay(1000);
  
  while((val_far1 == 1 && val_near1 == 1) || (val_far2 == 1 && val_near2 == 1)){
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
     
    if(digitalRead(ir_far1) ==LOW){
    val_far1 = 1;
    }
    if(digitalRead(ir_near1) ==LOW){
      val_near1 = 1;
    }
    if(digitalRead(ir_far2) ==LOW){
      val_far2 = 1;
    }
    if(digitalRead(ir_near2) ==LOW){
      val_near2 = 1;
    }
//    delay(5000);


  

    while((val_far1 == 1 && val_near1 == 1) && (val_far2 == 1 && val_near2 == 1)){
       Serial.println("Gate Open");
       val_far1 = 0;
       val_near1 = 0;
       val_far2 = 0;
       val_near2 = 0;
       
    }
//    if((val_far1 == 0 && val_near1 == 0) || (val_far2 == 0 && val_near2 == 0)){
//      Serial.println("Gate Open");
//    }
    
  }
  
   



}
