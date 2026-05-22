#ifndef MID_BLYNK_H
#define MID_BLYNK_H

#include <Arduino.h>
#include "Mid_sensor.h"

void Mid_Blynk_Init();
void Mid_Blynk_Run();
void Mid_Blynk_SendSensor(const SensorData &data);
void Mid_Blynk_SendActuatorState();

#endif