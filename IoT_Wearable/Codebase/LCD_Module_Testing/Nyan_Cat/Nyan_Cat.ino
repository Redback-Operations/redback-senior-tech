#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Define custom colors
#define ST77XX_PINK tft.color565(255, 105, 180) // RGB for pink
#define ST77XX_RED tft.color565(255, 0, 0)
#define ST77XX_ORANGE tft.color565(255, 165, 0)
#define ST77XX_YELLOW tft.color565(255, 255, 0)
#define ST77XX_GREEN tft.color565(0, 255, 0)
#define ST77XX_BLUE tft.color565(0, 0, 255)
#define ST77XX_INDIGO tft.color565(75, 0, 130)
#define ST77XX_VIOLET tft.color565(238, 130, 238)

int catX = 0;
int catY = 100; // Y position for Nyan Cat

void setup() {
  tft.init(240, 280);  // Initialize display with correct resolution
  tft.setRotation(2);  // Adjust rotation if needed
  tft.fillScreen(ST77XX_WHITE);  // Clear screen with white background
}

void loop() {
  tft.fillScreen(ST77XX_WHITE); // Clear the screen

  drawRainbow(catX, catY); // Draw rainbow behind the cat
  drawNyanCat(catX, catY); // Draw Nyan Cat

  catX += 2; // Move Nyan Cat to the right
  if (catX > tft.width()) { // Reset position if it goes off screen
    catX = -50; // Start from the left side
  }

  delay(50); // Control the speed of the animation
}

void drawNyanCat(int x, int y) {
  // Simple representation of Nyan Cat using rectangles and circles
  tft.fillRect(x, y, 50, 30, ST77XX_PINK); // Body
  tft.fillRect(x + 10, y - 10, 10, 10, ST77XX_BLACK); // Left ear
  tft.fillRect(x + 30, y - 10, 10, 10, ST77XX_BLACK); // Right ear

  // Eyes
  tft.fillCircle(x + 15, y + 10, 3, ST77XX_BLACK); // Left eye
  tft.fillCircle(x + 35, y + 10, 3, ST77XX_BLACK); // Right eye

  // Mouth
  tft.drawLine(x + 20, y + 15, x + 30, y + 15, ST77XX_BLACK); // Mouth
}

void drawRainbow(int x, int y) {
  // Draw a simple rainbow using rectangles
  int rainbowHeight = 10; // Height of each rainbow band
  tft.fillRect(x + 10, y + 20, 80, rainbowHeight, ST77XX_RED);
  tft.fillRect(x + 10, y + 20 + rainbowHeight, 80, rainbowHeight, ST77XX_ORANGE);
  tft.fillRect(x + 10, y + 20 + rainbowHeight * 2, 80, rainbowHeight, ST77XX_YELLOW);
  tft.fillRect(x + 10, y + 20 + rainbowHeight * 3, 80, rainbowHeight, ST77XX_GREEN);
  tft.fillRect(x + 10, y + 20 + rainbowHeight * 4, 80, rainbowHeight, ST77XX_BLUE);
  tft.fillRect(x + 10, y + 20 + rainbowHeight * 5, 80, rainbowHeight, ST77XX_INDIGO);
  tft.fillRect(x + 10, y + 20 + rainbowHeight * 6, 80, rainbowHeight, ST77XX_VIOLET);
}
