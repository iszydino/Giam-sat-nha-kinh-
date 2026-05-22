#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ================== BLYNK ==================
#define BLYNK_TEMPLATE_ID "TMPL6sR8WKRw4"
#define BLYNK_TEMPLATE_NAME "giam sat nha kinh"
#define BLYNK_AUTH_TOKEN "T4p8wMJIBSA5hA9TKNva330SbPmVS5Y6"

#define WIFI_SSID           "Redmi"
#define WIFI_PASS           "00000000"

// ================== CHAN DIEU KHIEN ==================
#define PIN_BOM             26
#define PIN_QUAT            27
#define PIN_DEN             32

// ================== CHAN CAM BIEN ==================
#define PIN_DHT22           14
#define PIN_LIGHT_AO        35
#define PIN_SOIL_AO         34

// ================== OLED I2C ==================
#define PIN_OLED_SCL        22
#define PIN_OLED_SDA        23

#define OLED_WIDTH          128
#define OLED_HEIGHT         64
#define OLED_ADDR           0x3C

// ================== MUC TAC DONG NGO RA ==================
#define RELAY_ON_LEVEL      HIGH
#define RELAY_OFF_LEVEL     LOW

#define LED_ON_LEVEL        HIGH
#define LED_OFF_LEVEL       LOW

// ================== NGUONG AUTO ==================
// Quat
#define TEMP_QUAT_ON        28.0
#define TEMP_QUAT_OFF       27.0

// Den
// Neu Light Raw < 700 thi coi la TOI
#define LIGHT_DARK_ADC      700

// Bom
// Dat kho -> soilPercent thap -> bat bom
#define SOIL_ON_PERCENT     35
#define SOIL_OFF_PERCENT    55

// Gia tri hieu chinh cam bien dat
#define SOIL_DRY_ADC        1200
#define SOIL_WET_ADC        3000

// ================== CHU KY ==================
#define SENSOR_PERIOD_MS    2500
#define DISPLAY_PERIOD_MS   2500
#define BLYNK_SEND_MS       2500

#endif