#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class RelayDriver {
public:
  RelayDriver(uint8_t pin, uint8_t onLevel);

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