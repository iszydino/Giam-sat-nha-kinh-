#include "Mid_sensor.h"
#include "Config.h"
#include "DHT22.h"
#include "Soid.h"
#include "light.h"

static DHT22Sensor dht22(PIN_DHT22);
static SoilSensor soilSensor(PIN_SOIL_AO, SOIL_DRY_ADC, SOIL_WET_ADC);
static LightSensor lightSensor(PIN_LIGHT_AO, LIGHT_DARK_ADC);

void Mid_Sensor_Init() {
  dht22.begin();
  soilSensor.begin();
  lightSensor.begin();

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_SOIL_AO, ADC_11db);
  analogSetPinAttenuation(PIN_LIGHT_AO, ADC_11db);
}

SensorData Mid_Sensor_Read() {
  SensorData data;

  data.dhtOk = dht22.read(data.temperature, data.humidity);

  if (!data.dhtOk) {
    data.temperature = -1000;
    data.humidity = -1;
  }

  data.soilRaw = soilSensor.readRaw();
  data.soilPercent = soilSensor.readPercent();

  data.lightRaw = lightSensor.readRaw();
  data.lightPercent = lightSensor.readPercent();
  data.isDark = lightSensor.isDark();

  return data;
}