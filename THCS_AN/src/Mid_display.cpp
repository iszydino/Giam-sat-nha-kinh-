#include "Mid_display.h"
#include "Config.h"
#include "Oled.h"

static OledDisplay oled;
static bool oledOk = false;

void Mid_Display_Init() {
  oledOk = oled.begin(PIN_OLED_SDA, PIN_OLED_SCL, OLED_ADDR);

  if (oledOk) {
    oled.splash();
    delay(1000);
  }
}

void Mid_Display_Show(const SensorData &s, const ActuatorState &a) {
  if (!oledOk) {
    return;
  }

  oled.clear();

  if (s.dhtOk) {
    oled.printLine(0, "T:" + String(s.temperature, 1) + "C H:" + String(s.humidity, 0) + "%");
  } else {
    oled.printLine(0, "DHT22 ERROR");
  }

  oled.printLine(1, "Soil:" + String(s.soilPercent) + "% R:" + String(s.soilRaw));
  oled.printLine(2, "Light:" + String(s.lightRaw) + " " + String(s.isDark ? "TOI" : "SANG"));
  oled.printLine(3, String("DEN :") + (a.denOn ? "ON" : "OFF"));
  oled.printLine(4, String("QUAT:") + (a.quatOn ? "ON" : "OFF"));
  oled.printLine(5, String("BOM :") + (a.bomOn ? "ON" : "OFF"));

  oled.show();
}