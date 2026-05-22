#include "DHT22.h"

DHT22Sensor::DHT22Sensor(uint8_t pin)
: _dht(pin, DHT22) {
}

void DHT22Sensor::begin() {
  _dht.begin();
}

bool DHT22Sensor::read(float &temperature, float &humidity) {
  humidity = _dht.readHumidity();
  temperature = _dht.readTemperature();

  if (isnan(temperature) || isnan(humidity)) {
    return false;
  }

  return true;
}