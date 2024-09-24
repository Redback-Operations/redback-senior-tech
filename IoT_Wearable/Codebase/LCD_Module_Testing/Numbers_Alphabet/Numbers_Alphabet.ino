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
  tft.setTextColor(ST77XX_BLACK);  // Set text color to black
  tft.setTextSize(2.5);  // Set text size
}

void loop() {
  printAlphabet();
  delay(5000);
  tft.fillScreen(ST77XX_WHITE);  // Clear screen
  
  printNumbers();
  delay(5000);
  tft.fillScreen(ST77XX_WHITE);  // Clear screen
}

void printAlphabet() {
  tft.setCursor(10, 10);
  tft.println("Alphabet:");
  
  int x = 10;
  int y = 40;
  
  for (char c = 'A'; c <= 'Z'; c++) {
    tft.setCursor(x, y);
    tft.print(c);
    x += 20;
    if (x > 220) {
      x = 10;
      y += 30;
    }
  }
}

void printNumbers() {
  tft.setCursor(10, 10);
  tft.println("Numbers 0-10:");
  
  int x = 10;
  int y = 40;
  
  for (int i = 0; i <= 10; i++) {
    tft.setCursor(x, y);
    tft.print(i);
    x += 40;
    if (x > 200) {
      x = 10;
      y += 30;
    }
  }
}
