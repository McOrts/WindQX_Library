/*
  WindQX Library
  Author: McOrts (Carlos Orts)
  Date : Octover 2024
*/

#include "Arduino.h"

#ifndef WINDQX_H
#define WINDQX_H

class WindQX {
  public:
    WindQX();
    bool Initialize();
  	String getData();
  	float getWind();
  	float getTemperature();

    float _windKH;
    float _temperatureDeg;
};

#endif