#include "light.h"

LightSensor::LightSensor(uint8_t pinAO, int darkThreshold)
: _pinAO(pinAO),
  _darkThreshold(darkThreshold) {
}

void LightSensor::begin() {
  pinMode(_pinAO, INPUT);
}

int LightSensor::readRaw() {
  return analogRead(_pinAO);
}

int LightSensor::readPercent() {
  int raw = readRaw();

  int percent = map(raw, 0, 4095, 0, 100);
  percent = constrain(percent, 0, 100);

  return percent;
}

bool LightSensor::isDark() {
  int raw = readRaw();

  // Theo cau hinh: raw < LIGHT_DARK_ADC thi la toi
  if (raw > _darkThreshold) {
    return true;
  } else {
    return false;
  }
}