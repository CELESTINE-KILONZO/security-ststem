#ifdef ESP32
#include <WiFi.h>
#include <WiFiClientSecure.h>
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

const char* ssid = "MW4";
const char* password = "A987654321P";
const char* serverName = "YourServerURL";  // Replace with your server URL
const char* apiKeyValue = "tPmAT5Ab3j7F9";

int ledPin = 2; // LED pin
int rssiValue = 0; // Store the RSSI value

// GPS Setup
SoftwareSerial ss(16, 17); // Arduino RX, TX pins
TinyGPS gps;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the ESP's IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize the web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    // Create an HTML page to display location information
    String html = "<html><body>";
    html += "<h1>ESP32 #1</h1>";

    // GPS Data
    smartdelay(1000);
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    html += "<p>Latitude: " + String(flat, 10) + "</p>";
    html += "<p>Longitude: " + String(flon, 10) + "</p>";

    rssiValue = WiFi.RSSI(); // Get the RSSI value
    html += "<p>Signal Strength: " + String(rssiValue) + " dBm</p>";
    html += "<p>Distance to ESP32 #2: " + String(calculateDistance(flat, flon, 42.0, -71.0)) + " meters</p>";
    // Add other information as needed

    // Post data to MySQL PHP Database
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + String(apiKeyValue)
                               + "&Latitude=" + String(flat, 10)
                               + "&Longitude=" + String(flon, 10)
                               + "&Signal_Strength=" + String(rssiValue);

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      // Free resources
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
  // Your main loop code here
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
