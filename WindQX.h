/*
  WindQX Library
  Author: McOrts (Carlos Orts)
  Date : Octover 2024
*/

#ifndef WINDQX_H
#define WINDQX_H

#include "Arduino.h"

class WindQX {
  private:
    float _windKH;
    float _temperatureDeg;
    String _status;
  public:
    WindQX();
    void Initialize();
  	String getData();
  	float getWind();
  	float getTemperature();
    String getStatus();
};

#endif