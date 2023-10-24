#define BLYNK_TEMPLATE_ID "TMPL84lh55xb"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "oEpV_ILQh7Q37g3gxEu_JKfjLmbNU6XT"

#define BLYNK_PRINT Serial 
#include <DHT.h>  
#include <SPI.h>
#include <ESP8266WiFi.h>       
#include <BlynkSimpleEsp8266.h>
// #include <SimpleTimer.h>



char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "1906";
char pass[] = "11111111"; 
int flag=0;  

/* DHT11*/
#include <DHT.h>
BlynkTimer timer;
#define DHTPIN D5 // DHT 11 : Temperature & humidity sensor connected to digital pin D0
#define DHTTYPE DHT11 // Sensor type : DHT11
DHT dht(DHTPIN, DHTTYPE); // Send DHT pin and type parameter to DHT Function 
float hum = 0; /* at init humidity is 0 */
float temp = 0;/* at init temp is 0*/
int sensorValue = 0;//New Line
int isButtonPressedValue = 0;//New Line 2
// #define DHTPIN D2         

// #define DHTTYPE DHT11     // DHT 11


// DHT dht(DHTPIN, DHTTYPE);

#define rainSensor A0
#define rainSensor_THRESHOLD 46 // adjust this value based on your sensor
// #define rainDigital D4



void sendSensor()
{
  
 
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V2, h);  //V1 is for Humidity
  Blynk.virtualWrite(V3, t);  //V0 is for Temperature
}

// Pin connected to the fan
const int fanPin = D1;   //For the fan
const int MotorPin = D0; //For the motor
// const int RainPin = D4;

 
  


void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(D3);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("CRYING");
    // Blynk.notify("Alert : Your Baby is Crying!!!");
 int isButtonPressedValue = digitalRead(D3);//New line 2
if (isButtonPressedValue ==1 && flag ==0) {
    Blynk.logEvent("crying");
  }///New line 2 end

Blynk.virtualWrite(V5, HIGH);  // Update the virtual pin associated with the button to indicate it's pressed
    flag=1;
  }
  else if (isButtonPressed==0)
Blynk.virtualWrite(V5, LOW);   // Update the virtual pin associated with the button to indicate it's released
  {
    flag=0;
  }
}

// BlynkTimer timer;

void moisture() {
  int rainSensor = analogRead(A0);
  rainSensor = map(rainSensor, 0, 1023, 0, 100);

  int sensorValue = analogRead(A0);//New line
if (sensorValue < rainSensor_THRESHOLD) {
    Blynk.logEvent("rainalert");
  }///New line end

  Blynk.virtualWrite(V0, rainSensor);
  Serial.println(rainSensor);
}

void setup()
{  

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
  timer.setInterval(1000L, sendSensor);
   pinMode(A0, INPUT);

  Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(D3,INPUT_PULLUP);
timer.setInterval(5L,notifyOnButtonPress); 
timer.setInterval(100L, moisture);


//  pinMode(A0, INPUT); 
pinMode(fanPin, OUTPUT);
pinMode(MotorPin, OUTPUT);
// pinMOde(RainPin, INPUT);
}

int sensor=0;
int output=0;

// void sendTemps()
// {
//  int sensor=analogRead(A0);
//   output=(100-map(sensor,0,1023,0,100));
//   Blynk.virtualWrite(V6,output); 
// // ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,//
// int rainAnalogVal = analogRead(rainAnalog);
//   // int rainDigitalVal = digitalRead(rainDigital);

//   Serial.print(rainAnalogVal);
//   Serial.print("\t");
//   // Serial.println(rainDigitalVal);
//   delay(200);
// }

void loop()
{

  // int sensorValue = analogRead(rainAnalog);
  // Serial.println("Rain sensor value: ");
  // Serial.println(sensorValue);

  // if (sensorValue < rainAnalog_THRESHOLD) {
  //   Blynk.logEvent("rainalert");
  // }

  // Blynk.virtualWrite(V0, sensorValue);



  
  Blynk.run(); 
  timer.run(); 
  // sendTemps();
}

BLYNK_WRITE(V1)
{
  int fanState = param.asInt();

  // Turn on/off the fan based on the Blynk app button state
  if (fanState == HIGH)
  {
    digitalWrite(fanPin, HIGH); // Turn on the fan
    Serial.println("Fan turned on");
  }
  else
  {
    digitalWrite(fanPin, LOW); // Turn off the fan
    Serial.println("Fan turned off");
  }
}

BLYNK_WRITE(V4)
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

// BLYNK_WRITE(V5)
// {
//   int buttonState = param.asInt();
//   int sensorValue = analogRead(sensorPin);
//   Serial.println(sensorValue);


//   if (sensorValue > 555)
//   {
//     Serial.println("CRYING");
//     // Blynk.notify("Alert: Your Baby is Crying!!!");
//     Blynk.virtualWrite(V5, HIGH);  // Update the virtual pin associated with the button to indicate it's pressed
//     flag = 1;
//   }
//   else if (sensorValue < 555)
//   {
//     Blynk.virtualWrite(V5, LOW);  // Update the virtual pin associated with the button to indicate it's released
//     flag = 0;
//   }
// }

// // BLYNK_WRITE(V5)
// // {
// //   int buttonState = param.asInt();

// //   if (buttonState == HIGH && flag == 0)
// //   {
// //     Serial.println("CRYING");
//     // Blynk.notify("Alert: Your Baby is Crying!!!");
//     Blynk.virtualWrite(V5, HIGH);  // Update the virtual pin associated with the button to indicate it's pressed
//     flag = 1;
//   }
//   else if (buttonState == LOW)
//   {
//     Blynk.virtualWrite(V5, LOW);  // Update the virtual pin associated with the button to indicate it's released
//     flag = 0;
//   }
// }


  
  



