#ifndef WINDQX_H
#define WINDQX_H

#include "Arduino.h"

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