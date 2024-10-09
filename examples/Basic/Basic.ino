/*******************************************************************
  This is a basic example sketch to show the working of this library:
  Download the library here- https://github.com/McOrts/WindQX_Library
  With these devices: https://ecdsl.com/en/categoria-producto/windqx/
  Author: McOrts (Carlos Orts)
  Date : October 2024
 * ****************************************************************
  Pinout connection for Arduino UNO

  WindQX SA.01 pin | Arduino UNO pin
    - (black)      | GND
    + (red)        | 5V
   RX (white)      | PIN 1 (TX)
   TX (yellow)     | PIN 0 (RX)
 * ****************************************************************
  IMPORTANT: remove PIN 1 (TX) before uploading this sketch
 * *****************************************************************/

#include "Arduino.h"
#include "WindQX.h"

WindQX SA01;

void setup() {
  SA01.Initialize();
}

void loop() {
  if (SA01.getData() = "OK") {                  // get All data from WindQX device
    float temperature = SA01.getTemperature();  // return temperature in celsius
    float wind = SA01.getWind();                // return wind speed in Km/h
    Serial.printf("Temperature: %0.1lf°C  Wind speed: %0.1lfKm/h \n", temperature, wind);
  } else {
      Serial.println(SA01.getStatus());
  }
  delay(2000);  
}
