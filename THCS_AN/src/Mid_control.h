#ifndef MID_CONTROL_H
#define MID_CONTROL_H

#include <Arduino.h>
#include "Mid_sensor.h"

struct ActuatorState {
  bool bomOn;
  bool quatOn;
  bool denOn;

  bool autoMode;

  bool bomAuto;
  bool quatAuto;
  bool denAuto;

  bool bomManual;
  bool quatManual;
  bool denManual;
};

void Mid_Control_Init();

void Mid_Control_SetAutoMode(bool enable);
void Mid_Control_SetBom(bool state);
void Mid_Control_SetQuat(bool state);
void Mid_Control_SetDen(bool state);

void Mid_Control_UpdateAuto(const SensorData &data);
void Mid_Control_AllOff();

ActuatorState Mid_Control_GetState();

#endif