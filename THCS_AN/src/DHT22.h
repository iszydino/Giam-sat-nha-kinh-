#ifndef DHT22_SENSOR_H
#define DHT22_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

class DHT22Sensor {
public:
  explicit DHT22Sensor(uint8_t pin);

  void begin();
  bool read(float &temperature, float &humidity);

private:
  DHT _dht;
};

#endif