/*
  WindQX Library
  Author: McOrts (Carlos Orts)
  Date : Octover 2024
*/

#include "Arduino.h"

WindQX::WindQX() {
}

bool WindQX::Initialize() {
    Serial.begin(115200);
    return True;
}

String WindQX::getData() {
  if (Serial.available() > 0) {
    /* reading variables */
    unsigned int PWM;
    float WSPE;
    float TEMP;
    unsigned int CRC;
    String FRAME;

    FRAME = Serial.readStringUntil('\n'); // Read the FRAME until a line break is found
    Serial.println(FRAME);

    // Divide the frame into its components separated by spaces.
    int values[4];
    int counter = 0;
    char *ptr = strtok((char *)FRAME.c_str(), " ");
    while (ptr != NULL && counter < 4) {
      values[counter] = atoi(ptr);
      ptr = strtok(NULL, " ");
      counter++;
    }

    // Check that the 4 expected values ​​have been found
    if (counter == 4) {
      PWM = values[0];
      WSPE = values[1];
      TEMP = values[2];
      CRC = values[3];
      // measures calibration
      _temperatureDeg = TEMP / 100 - 40;
      _windKH = WSPE / 10;
      if (wind > 200) {
        _windKH = 0;
        _status = "Wet sensor";
        return "KO";
      } else {
        _status = "Ok";
        return "OK";
      }
    } else {
      while (Serial.available() > 0) {
        Serial.read(); // Read and discard the incoming byte
      }
      _status = "Reading error";
      return "KO";
    }
  }
}

float WindQX::getWind() {
  return _windKH;
}

float WindQX::getTemperature() {
  return _temperatureDeg;
}

String WindQX::getStatus() {
  return _status;
}