#include "Soid.h"

SoilSensor::SoilSensor(uint8_t pin, int adcDry, int adcWet)
: _pin(pin),
  _adcDry(adcDry),
  _adcWet(adcWet) {
}

void SoilSensor::begin() {
  pinMode(_pin, INPUT);
}

int SoilSensor::readRaw() {
  return analogRead(_pin);
}

int SoilSensor::readPercent() {
  int raw = readRaw();

  // Dat kho -> 0%
  // Dat uot -> 100%
  long percent = map(raw, _adcDry, _adcWet, 0, 100);
  percent = constrain(percent, 0, 100);

  return (int)percent;
}