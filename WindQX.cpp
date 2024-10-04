#include "Arduino.h"


WindQX::WindQX() {
}

bool WindQX::Initialize() {
    Serial.begin(115200);
    return True;
}

String WindQX::getData() {

}

float WindQX::getWind() {
  return _windKH;
}

float WindQX::getTemperature() {
  return _temperatureDeg;
}