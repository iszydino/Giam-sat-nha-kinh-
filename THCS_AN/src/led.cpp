#include "led.h"

LedDriver::LedDriver(uint8_t pin, uint8_t onLevel)
: _pin(pin),
  _onLevel(onLevel),
  _offLevel(onLevel == HIGH ? LOW : HIGH),
  _state(false) {
}

void LedDriver::begin() {
  pinMode(_pin, OUTPUT);
  off();
}

void LedDriver::on() {
  digitalWrite(_pin, _onLevel);
  _state = true;
}

void LedDriver::off() {
  digitalWrite(_pin, _offLevel);
  _state = false;
}

void LedDriver::set(bool state) {
  if (state) {
    on();
  } else {
    off();
  }
}

bool LedDriver::isOn() const {
  return _state;
}