#include "Oled.h"
#include "Config.h"

OledDisplay::OledDisplay()
: _display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1) {
}

bool OledDisplay::begin(uint8_t sda, uint8_t scl, uint8_t addr) {
  Wire.begin(sda, scl);

  if (!_display.begin(SSD1306_SWITCHCAPVCC, addr)) {
    return false;
  }

  _display.clearDisplay();
  _display.setTextColor(SSD1306_WHITE);
  _display.display();

  return true;
}

void OledDisplay::clear() {
  _display.clearDisplay();
  _display.setTextColor(SSD1306_WHITE);
}

void OledDisplay::printLine(uint8_t row, const String &text, uint8_t size) {
  _display.setTextSize(size);
  _display.setCursor(0, row * 10);
  _display.print(text);
}

void OledDisplay::show() {
  _display.display();
}

void OledDisplay::splash() {
  clear();

  _display.setTextSize(1);
  _display.setCursor(0, 0);
  _display.println("ESP32 SENSOR SYSTEM");
  _display.println("DHT22 + LIGHT + SOIL");
  _display.println("OLED OK");

  _display.display();
}