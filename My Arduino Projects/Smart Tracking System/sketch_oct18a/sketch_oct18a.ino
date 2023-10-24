#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>

const int RXPin = 4, TXPin = 5;
SoftwareSerial neo6m(RXPin, TXPin);

TinyGPSPlus gps;

const char *ssid = "Shamila"; // Change to your WiFi network name
const char *password = "aaaaaaaa"; // Change to your WiFi password

String GMAP_API_KEY = "AIzaSyBqQaUpA96TYXCGPOls82chHxR0HOOtsWs"; // Replace with your Google Maps API Key

WiFiServer server(80);

String html;

void setup() {
  Serial.begin(115200);
  Serial.println();
  neo6m.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  smartdelay_gps(1000);

  if (gps.location.isValid()) {
    String latitude = String(gps.location.lat(), 6);
    String longitude = String(gps.location.lng(), 6);

    WiFiClient client = server.available();
    if (client) {
      String currentLine = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");
              client.println();
              client.println(html);
              break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {
            currentLine += c;
          }
        }
      }
      client.stop();
      Serial.println("Client disconnected");
    }
  }
}

static void smartdelay_gps(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (neo6m.available())
      gps.encode(neo6m.read());
  } while (millis() - start < ms);
}

void buildHTML(String &html, String latitude, String longitude) {
  html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
  html += "<title>My Google Map</title>";
  html += "<style>#map{height:400px;width:100%;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>My Google Map</h1>";
  html += "<div id='map'></div>";
  html += "<script>";
  html += "var map;";
  html += "var marker;";
  html += "var INTERVAL = 5000;";

  html += "function initMap() {";
  html += "var options = {";
  html += "zoom: 16,";
  html += "center: {lat: " + latitude + ", lng: " + longitude + "},";
  html += "mapTypeId: google.maps.MapTypeId.ROADMAP,";
  html += "};";
  html += "map = new google.maps.Map(document.getElementById('map'), options);";
  html += "}";

  html += "function getMarkers() {";
  html += "var newLatLng = new google.maps.LatLng(" + latitude + ", " + longitude + ");";
  html += "marker = new google.maps.Marker({";
  html += "position: newLatLng,";
  html += "map: map";
  html += "});";
  html += "}";

  html += "window.setInterval(getMarkers, INTERVAL);";
  html += "</script>";
  html += "<script async defer src='https://maps.googleapis.com/maps/api/js?key=" + GMAP_API_KEY + "&callback=initMap'></script>";
  html += "</body></html>";
}
