#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.init(240, 280);  // Initialize display with correct resolution
  tft.setRotation(2);  // Adjust rotation if needed
  tft.fillScreen(ST77XX_WHITE);  // Clear screen with white background


}

void loop() {

  drawHeart(120, 140, 100);  // Draw heart at position (120, 140) with size 100
  delay(5000);
  tft.fillScreen(ST77XX_WHITE);  // Clear screen with white background

  drawSmile(120, 170, 100);    // Draw smile face below the heart
  delay(5000);
  tft.fillScreen(ST77XX_WHITE);  // Clear screen with white background
}

void drawHeart(int x, int y, int size) {
  // Draw the left side of the heart
  tft.fillCircle(x - size / 2, y - size / 2, size / 2, ST77XX_RED);
  tft.fillCircle(x + size / 2, y - size / 2, size / 2, ST77XX_RED);
  
  // Draw the bottom triangle of the heart
  tft.fillTriangle(x - size, y, x + size, y, x, y + size, ST77XX_RED);
  
  // Draw rectangle to fill the space between circles and triangle
  tft.fillRect(x - size, y - size / 2, size * 2, size / 2, ST77XX_RED);
}

void drawSmile(int x, int y, int size) {
  // Draw the smile using lines
  for (int i = -size; i <= size; i++) {
    int yOffset = sqrt(size * size - i * i); // Calculate y offset for the smile curve
    tft.drawPixel(x + i, y + yOffset / 2, ST77XX_BLACK); // Draw the smile curve
  }

  // Draw the eyes
  tft.fillCircle(x - size / 3, y - size / 4, size / 10, ST77XX_BLACK); // Left eye
  tft.fillCircle(x + size / 3, y - size / 4, size / 10, ST77XX_BLACK); // Right eye
}