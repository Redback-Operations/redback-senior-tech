#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// Pin definitions for the display
#define TFT_CS     10  // Chip select control pin
#define TFT_RST    8   // Reset pin
#define TFT_DC     9   // Data/command control pin

// Initialize ST7789 display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the display
  tft.init(240, 280); // Initialize ST7789 display with 240x280 resolution

  // Optional: Set rotation of the display (0-3)
  tft.setRotation(1);

  // Create a gradient background
  drawGradientBackground();

  // Display "Hello" message
  displayHelloMessage();
}

void loop() {
  // You can add more code here if needed
}

// Function to create a simple gradient background
void drawGradientBackground() {
  uint16_t color;
  
  // Loop through each row (240 rows in total for 240x280 display)
  for (int y = 0; y < 240; y++) {
    // Create a color gradient from red to blue
    color = tft.color565(y, 0, 255 - y);  // Red -> Blue gradient
    tft.drawFastHLine(0, y, 280, color);  // Draw a horizontal line of this color
  }
}

// Function to display "Hello" message in the center of the screen
void displayHelloMessage() {
  // Set text properties
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);  // Set text size
  tft.setCursor(100, 100); // Adjust to center the text
  
  // Print "Hello" on the screen
  tft.print("Hello");
}
