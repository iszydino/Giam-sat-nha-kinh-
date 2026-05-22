#ifndef MID_DISPLAY_H
#define MID_DISPLAY_H

#include <Arduino.h>
#include "Mid_sensor.h"
#include "Mid_control.h"

void Mid_Display_Init();
void Mid_Display_Show(const SensorData &sensor, const ActuatorState &act);

#endif