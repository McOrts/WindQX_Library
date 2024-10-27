/*******************************************************************
  This is a advanced example sketch to show the working of this library.
  Based on esp32-web-server-gauges of Rui Santos & Sara Santos - Random Nerd Tutorials 
  Download the library here: https://github.com/McOrts/WindQX_Library
  For these devices: https://ecdsl.com/en/categoria-producto/windqx/
  Author: McOrts (Carlos Orts)
  Date : November 2024
 * ****************************************************************
  Pinout connection for EXP32

  WindQX SA.01 pin | ESP32 WROOM pin
    - (black)      | GND
    + (red)        | Vin (5V)
   RX (white)      | PIN 35 (TXD)
   TX (yellow)     | PIN 34 (RXD)
 * ****************************************************************
  IMPORTANT: remove PIN 35 (TXD) before uploading this sketch
 * *****************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include "WindQX.h"

// Replace with your network credentials
const char* ssid = "¿?";
const char* password = "¿?";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 500;

// Create a sensor object
WindQX SA01;

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  // Init WindQX sensor
  SA01.Initialize();

  initWiFi();
  initLittleFS();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");

  // Request for the latest sensor readings
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
  });

  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  // Start server
  server.begin();
}

// Get Sensor Readings and return JSON object
String getSensorReadings(){
  if (SA01.getData() = "OK") {                  // get All data from WindQX device
    float temperature = SA01.getTemperature();  // return temperature in celsius
    float wind = SA01.getWind();                // return wind speed in Km/h
    Serial.printf("Temperature: %0.1lf°C  Wind speed: %0.1lfKm/h \n", temperature, wind);
    readings["temperature"] = String(temperature);
    readings["speed"] =  String(wind);
    String jsonString = JSON.stringify(readings);
    return jsonString;
  } else {
      Serial.println(SA01.getStatus());
  }
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    Serial.flush();
    // Send Events to the client with the Sensor Readings Every timerDelay seconds
    events.send("ping",NULL,millis());
    events.send(getSensorReadings().c_str(),"new_readings" ,millis());
    lastTime = millis();
  }
}