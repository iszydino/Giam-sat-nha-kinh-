#include <Arduino.h>
#include "Config.h"
#include "Mid_sensor.h"
#include "Mid_control.h"
#include "Mid_display.h"
#include "Mid_blynk.h"

static SensorData sensorData;
static ActuatorState actuatorState;

static unsigned long lastSensorMs = 0;
static unsigned long lastDisplayMs = 0;

void printSerialData(const SensorData &s, const ActuatorState &a) {
  Serial.println("========== SENSOR DATA ==========");

  if (s.dhtOk) {
    Serial.print("Nhiet do: ");
    Serial.print(s.temperature);
    Serial.println(" C");

    Serial.print("Do am khong khi: ");
    Serial.print(s.humidity);
    Serial.println(" %");
  } else {
    Serial.println("DHT22: LOI DOC");
  }

  Serial.print("Soil Raw: ");
  Serial.println(s.soilRaw);

  Serial.print("Soil Percent: ");
  Serial.print(s.soilPercent);
  Serial.println(" %");

  Serial.print("Light Raw: ");
  Serial.println(s.lightRaw);

  Serial.print("Anh sang: ");
  Serial.println(s.isDark ? "TOI" : "SANG");

  Serial.print("Mode: ");
  Serial.println(a.autoMode ? "AUTO" : "MANUAL");

  Serial.print("DEN: ");
  Serial.println(a.denOn ? "ON" : "OFF");

  Serial.print("QUAT: ");
  Serial.println(a.quatOn ? "ON" : "OFF");

  Serial.print("BOM: ");
  Serial.println(a.bomOn ? "ON" : "OFF");

  Serial.println("=================================");
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Mid_Sensor_Init();
  Mid_Control_Init();
  Mid_Display_Init();
  Mid_Blynk_Init();

  Serial.println("ESP32 IOT STARTED");
  Serial.println("V20 = 1 AUTO, V20 = 0 MANUAL");
}

void loop() {
  unsigned long now = millis();

  Mid_Blynk_Run();

  if (now - lastSensorMs >= SENSOR_PERIOD_MS) {
    lastSensorMs = now;

    sensorData = Mid_Sensor_Read();

    // Luong 1: AUTO control
    Mid_Control_UpdateAuto(sensorData);

    actuatorState = Mid_Control_GetState();

    // Gui du lieu len Blynk
    Mid_Blynk_SendSensor(sensorData);
    Mid_Blynk_SendActuatorState();

    printSerialData(sensorData, actuatorState);
  }

  if (now - lastDisplayMs >= DISPLAY_PERIOD_MS) {
    lastDisplayMs = now;

    actuatorState = Mid_Control_GetState();
    Mid_Display_Show(sensorData, actuatorState);
  }
}