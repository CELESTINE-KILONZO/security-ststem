#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

const char* ssid = "cele";
const char* password = "cele464230";
const char* serverName = "http://hyperesearchconsultants.com/alexresearchdatasets_FixedIntervalsNode/dbwrite.php";
const char* apiKeyValue = "tPmAT5Ab3j7F9";

int ledPin = 4;
int rssiValue = 0;

SoftwareSerial ss(16, 17);
TinyGPS gps;

AsyncWebServer server(80);

unsigned long previousMillis = 0;
const long interval = 30 * 1000; // 30 seconds interval
int dataInstancesSent = 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  ss.begin(9600);

  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = "<html><body>";
    html += "<h1>VIP SECURITY</h1>";

    smartdelay(1000);
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    html += "<p>Latitude: " + String(flat, 10) + "</p>";
    html += "<p>Longitude: " + String(flon, 10) + "</p>";

    rssiValue = WiFi.RSSI();
    html += "<p>Signal Strength: " + String(rssiValue) + " dBm</p>";
    html += "<p>Distance to VIP TRACKER: " + String(calculateDistance(flat, flon, 42.0, -71.0)) + " meters</p>";

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + String(apiKeyValue) +
                              "&Latitude_S2=" + String(flat, 10) +
                              "&Longitude_S2=" + String(flon, 10) +
                              "&Signal_Strength2=" + String(rssiValue);

      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String response = http.getString();
        Serial.println("Server response: " + response);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }

    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
}



void loop() {
  // put your main code here, to run repeatedly:
 unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // It's time to send another data instance
    previousMillis = currentMillis;
    
    if (dataInstancesSent < 4) {
      // Post data to the server
      Serial.println("Sending data instance " + String(dataInstancesSent + 1));
      sendDataToServer();
      dataInstancesSent++;
    } else {
      // All data instances sent, reset the count
      dataInstancesSent = 0;
    }
  }

  // Your other loop code here
}

void sendDataToServer() {
  // Code to send data to the server (same as in the setup function)
  // ...
}

double calculateDistance(float lat1, float lon1, float lat2, float lon2) {
  // Haversine formula to calculate distance between two GPS coordinates
  const double R = 6371000; // Earth radius in meters
  double dlat = radians(lat2 - lat1);
  double dlon = radians(lon2 - lon1);
  double a = sin(dlat / 2) * sin(dlat / 2) + cos(radians(lat1)) * cos(radians(lat2)) * sin(dlon / 2) * sin(dlon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return R * c;
}

static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
