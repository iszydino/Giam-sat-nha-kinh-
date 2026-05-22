#ifndef MID_SENSOR_H
#define MID_SENSOR_H

#include <Arduino.h>

struct SensorData {
  float temperature;
  float humidity;

  int soilRaw;
  int soilPercent;

  int lightRaw;
  int lightPercent;
  bool isDark;

  bool dhtOk;
};

void Mid_Sensor_Init();
SensorData Mid_Sensor_Read();

#endif