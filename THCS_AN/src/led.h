#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LedDriver {
public:
  LedDriver(uint8_t pin, uint8_t onLevel);

  void begin();
  void on();
  void off();
  void set(bool state);
  bool isOn() const;

private:
  uint8_t _pin;
  uint8_t _onLevel;
  uint8_t _offLevel;
  bool _state;
};

#endif