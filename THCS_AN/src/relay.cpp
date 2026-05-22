#include "relay.h"

RelayDriver::RelayDriver(uint8_t pin, uint8_t onLevel)
: _pin(pin),
  _onLevel(onLevel),
  _offLevel(onLevel == HIGH ? LOW : HIGH),
  _state(false) {
}

void RelayDriver::begin() {
  pinMode(_pin, OUTPUT);
  off();
}

void RelayDriver::on() {
  digitalWrite(_pin, _onLevel);
  _state = true;
}

void RelayDriver::off() {
  digitalWrite(_pin, _offLevel);
  _state = false;
}

void RelayDriver::set(bool state) {
  if (state) {
    on();
  } else {
    off();
  }
}

bool RelayDriver::isOn() const {
  return _state;
}