#include "Config.h"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include "Mid_blynk.h"
#include "Mid_control.h"

// ================== VIRTUAL PIN DU LIEU ==================
#define VPIN_TEMP          V0
#define VPIN_HUMI          V1
#define VPIN_SOIL_PERCENT  V2
#define VPIN_SOIL_RAW      V3
#define VPIN_LIGHT_RAW     V4
#define VPIN_LIGHT_STATUS  V5

// ================== VIRTUAL PIN DIEU KHIEN ==================
#define VPIN_DEN_CTRL      V10
#define VPIN_QUAT_CTRL     V11
#define VPIN_BOM_CTRL      V12

// ================== VIRTUAL PIN TRANG THAI ==================
#define VPIN_DEN_STATE     V13
#define VPIN_QUAT_STATE    V14
#define VPIN_BOM_STATE     V15

// ================== VIRTUAL PIN MODE ==================
#define VPIN_AUTO_MODE     V20

void Mid_Blynk_Init() {
  Serial.println("Dang ket noi WiFi va Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  Serial.println("Blynk connected");
}

void Mid_Blynk_Run() {
  Blynk.run();
}

void Mid_Blynk_SendSensor(const SensorData &data) {
  if (data.dhtOk) {
    Blynk.virtualWrite(VPIN_TEMP, data.temperature);
    Blynk.virtualWrite(VPIN_HUMI, data.humidity);
  } else {
    Blynk.virtualWrite(VPIN_TEMP, 0);
    Blynk.virtualWrite(VPIN_HUMI, 0);
  }

  Blynk.virtualWrite(VPIN_SOIL_PERCENT, data.soilPercent);
  Blynk.virtualWrite(VPIN_SOIL_RAW, data.soilRaw);

  Blynk.virtualWrite(VPIN_LIGHT_RAW, data.lightRaw);
  Blynk.virtualWrite(VPIN_LIGHT_STATUS, data.isDark ? "TOI" : "SANG");
}

void Mid_Blynk_SendActuatorState() {
  ActuatorState st = Mid_Control_GetState();

  Blynk.virtualWrite(VPIN_DEN_STATE, st.denOn ? 1 : 0);
  Blynk.virtualWrite(VPIN_QUAT_STATE, st.quatOn ? 1 : 0);
  Blynk.virtualWrite(VPIN_BOM_STATE, st.bomOn ? 1 : 0);

  Blynk.virtualWrite(VPIN_AUTO_MODE, st.autoMode ? 1 : 0);
}

// ================== LENH TU BLYNK APP ==================
// Cac nut V10, V11, V12 chi dieu khien khi V20 = 0, tuc MANUAL.

BLYNK_WRITE(VPIN_AUTO_MODE) {
  int value = param.asInt();

  if (value == 1) {
    Mid_Control_SetAutoMode(true);
    Serial.println("Blynk: AUTO MODE");
  } else {
    Mid_Control_SetAutoMode(false);
    Serial.println("Blynk: MANUAL MODE");
  }

  Mid_Blynk_SendActuatorState();
}

BLYNK_WRITE(VPIN_DEN_CTRL) {
  int value = param.asInt();

  Mid_Control_SetDen(value == 1);

  Serial.print("Blynk Manual DEN = ");
  Serial.println(value);

  Mid_Blynk_SendActuatorState();
}

BLYNK_WRITE(VPIN_QUAT_CTRL) {
  int value = param.asInt();

  Mid_Control_SetQuat(value == 1);

  Serial.print("Blynk Manual QUAT = ");
  Serial.println(value);

  Mid_Blynk_SendActuatorState();
}

BLYNK_WRITE(VPIN_BOM_CTRL) {
  int value = param.asInt();

  Mid_Control_SetBom(value == 1);

  Serial.print("Blynk Manual BOM = ");
  Serial.println(value);

  Mid_Blynk_SendActuatorState();
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(VPIN_AUTO_MODE);
  Blynk.syncVirtual(VPIN_DEN_CTRL);
  Blynk.syncVirtual(VPIN_QUAT_CTRL);
  Blynk.syncVirtual(VPIN_BOM_CTRL);

  Mid_Blynk_SendActuatorState();
}