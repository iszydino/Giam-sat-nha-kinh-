#include "Mid_control.h"
#include "Config.h"
#include "relay.h"
#include "led.h"

static RelayDriver bom(PIN_BOM, RELAY_ON_LEVEL);
static RelayDriver quat(PIN_QUAT, RELAY_ON_LEVEL);
static LedDriver den(PIN_DEN, LED_ON_LEVEL);

static ActuatorState state = {
  false,  // bomOn
  false,  // quatOn
  false,  // denOn

  true,   // autoMode

  false,  // bomAuto
  false,  // quatAuto
  false,  // denAuto

  false,  // bomManual
  false,  // quatManual
  false   // denManual
};

static void Mid_Control_ApplyOutput() {
  if (state.autoMode) {
    state.bomOn = state.bomAuto;
    state.quatOn = state.quatAuto;
    state.denOn = state.denAuto;
  } else {
    state.bomOn = state.bomManual;
    state.quatOn = state.quatManual;
    state.denOn = state.denManual;
  }

  bom.set(state.bomOn);
  quat.set(state.quatOn);
  den.set(state.denOn);
}

void Mid_Control_Init() {
  bom.begin();
  quat.begin();
  den.begin();

  Mid_Control_AllOff();
}

void Mid_Control_SetAutoMode(bool enable) {
  state.autoMode = enable;
  Mid_Control_ApplyOutput();
}

void Mid_Control_SetBom(bool stateBom) {
  state.bomManual = stateBom;
  Mid_Control_ApplyOutput();
}

void Mid_Control_SetQuat(bool stateQuat) {
  state.quatManual = stateQuat;
  Mid_Control_ApplyOutput();
}

void Mid_Control_SetDen(bool stateDen) {
  state.denManual = stateDen;
  Mid_Control_ApplyOutput();
}

void Mid_Control_UpdateAuto(const SensorData &data) {
  // ================== AUTO QUAT ==================
  if (data.dhtOk) {
    if (state.quatAuto) {
      if (data.temperature <= TEMP_QUAT_OFF) {
        state.quatAuto = false;
      }
    } else {
      if (data.temperature > TEMP_QUAT_ON) {
        state.quatAuto = true;
      }
    }
  } else {
    state.quatAuto = false;
  }

  // ================== AUTO DEN ==================
  if (data.isDark) {
    state.denAuto = true;
  } else {
    state.denAuto = false;
  }

  // ================== AUTO BOM ==================
  if (state.bomAuto) {
    if (data.soilPercent >= SOIL_OFF_PERCENT) {
      state.bomAuto = false;
    }
  } else {
    if (data.soilPercent <= SOIL_ON_PERCENT) {
      state.bomAuto = true;
    }
  }

  Mid_Control_ApplyOutput();
}

void Mid_Control_AllOff() {
  state.bomAuto = false;
  state.quatAuto = false;
  state.denAuto = false;

  state.bomManual = false;
  state.quatManual = false;
  state.denManual = false;

  state.bomOn = false;
  state.quatOn = false;
  state.denOn = false;

  bom.off();
  quat.off();
  den.off();
}

ActuatorState Mid_Control_GetState() {
  return state;
}