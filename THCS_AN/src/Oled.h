#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OledDisplay {
public:
  OledDisplay();

  bool begin(uint8_t sda, uint8_t scl, uint8_t addr);
  void clear();
  void printLine(uint8_t row, const String &text, uint8_t size = 1);
  void show();
  void splash();

private:
  Adafruit_SSD1306 _display;
};

#endif