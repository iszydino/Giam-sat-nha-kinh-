#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

class LightSensor {
public:
  LightSensor(uint8_t pinAO, int darkThreshold);

  void begin();
  int readRaw();
  int readPercent();
  bool isDark();

private:
  uint8_t _pinAO;
  int _darkThreshold;
};

#endif