#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         7
#define TFT_BACKLIGHT  9  // Connect backlight to a PWM pin, e.g., 9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.init(240, 280);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_WHITE);
  
  pinMode(TFT_BACKLIGHT, OUTPUT);
  analogWrite(TFT_BACKLIGHT, 255);  // Start with full brightness
}

void loop() {
  fadeBacklight();
  delay(2000);
  tft.fillScreen(ST77XX_WHITE);
  
  pulseBacklight();
  delay(2000);
  tft.fillScreen(ST77XX_WHITE);
}

void fadeBacklight() {
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(TFT_BACKLIGHT, brightness);
    delay(10);
  }
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(TFT_BACKLIGHT, brightness);
    delay(10);
  }
}

void pulseBacklight() {
  for (int i = 0; i < 5; i++) {
    analogWrite(TFT_BACKLIGHT, 255);
    delay(100);
    analogWrite(TFT_BACKLIGHT, 50);
    delay(100);
  }
  analogWrite(TFT_BACKLIGHT, 255);  // Return to full brightness
}
