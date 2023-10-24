#define BLYNK_TEMPLATE_ID "TMPL6XvAyAQxS"
#define BLYNK_TEMPLATE_NAME "Smart waterlevel detection system using IOT"
#define BLYNK_AUTH_TOKEN "mdx3UQuTyYFt1KK5-YFOTvRDrThmKbKk"



#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define trigPin D5
#define echoPin D6
long duration;
int distance; 
float level;






char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Shamila";
char pass[] = "aaaaaaaa";

// int value = 0;
const int MotorPin = D0;

  //  BLYNK_WRITE(V0){
  // int value = param.asInt();
  // value ? digitalWrite(D0, HIGH) : digitalWrite(D0, LOW);
  // }
void ultrasonic()
{
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0340 / 2;//Formula to calculate the distance for ultrasonic sensor

  Blynk.virtualWrite(V1, distance);
    delay(500); 

}

void notifyOnButtonPress()
{
 
  if (distance==10) {
    Serial.println("TANK FULL");
    // Blynk.notify("Alert : Your Baby is Crying!!!");

  }
}
  void setup(){


  Serial.begin(9600);
//  pinMOde(D6, INPUT) ;
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);


  Serial.print("Connecting to Wifi Network");
   Serial.println(ssid);
//  WiFi.begin(ssid, password);
   Blynk.begin(auth, ssid, pass);
   Serial.println("Serial started");

 pinMode(MotorPin, OUTPUT);
}



void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0340 / 2;
  Serial.println("Distance");
  Serial.println(distance);



  level =((14-distance)/14.0)*100;
  Serial.println("level");
  Serial.println(level);
  delay(1000);




  Blynk.run();
  ultrasonic();
  // timer.run();
  // sendTemps();
}


BLYNK_WRITE(V0)
{
  int MotorState = param.asInt();

  // Turn on/off the fan based on the Blynk app button state
  if (MotorState == HIGH)
  {
    digitalWrite(MotorPin, HIGH); // Turn on the fan
    Serial.println("Motor turned on");
  }
  else
  {
    digitalWrite(MotorPin, LOW); // Turn off the fan
    Serial.println("Motor turned off");
  }
}



