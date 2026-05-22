#ifndef SOID_H
#define SOID_H

#include <Arduino.h>

class SoilSensor {
public:
  SoilSensor(uint8_t pin, int adcDry, int adcWet);

  void begin();
  int readRaw();
  int readPercent();

private:
  uint8_t _pin;
  int _adcDry;
  int _adcWet;
};

#endif