// This is used for:
// - Arduino Nano 33 IoT board, paired with
// - WaveShare ST7789v2 display module

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789, used for initializing display object
#include <SPI.h>

//Setting up the pins 
  #define TFT_CS        10
  #define TFT_RST        8
  #define TFT_DC         9

// We are using the HARDWARE SPI pins for MOSI and SCLK, which are unique
// to each board and not reassignable. For Arduino Nano 33 IoT: MOSI = pin 11 and
// SCLK = pin 13. This is done to improve the performance of the display.

// Create a display object of the Adafruit_ST7789 class
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Draw a battery icon with empty interior to display percentage
void drawBatteryIcon(int x, int y, uint16_t color) {
  tft.drawRect(x, y, 50, 25, color);          // Outer rectangle (battery body)
  tft.fillRect(x + 52, y + 7, 5, 12, color);   // Battery terminal
  tft.fillRect(x + 2, y + 2, 46, 21, ST77XX_BLACK);  // Inner fill (empty battery)
  
  // Display the percentage inside the battery icon
  tft.setCursor(x + 8, y + 5); //Set position
  tft.setTextColor(color); //Set color
  tft.setTextSize(2);  // Larger text size for better visibility
  tft.print("80%");  // Display the percentage inside the battery icon
}

// Draw a heart icon with heart rate text next to it
void drawHeartIcon(int x, int y, uint16_t color) {
  tft.fillCircle(x + 4, y + 4, 4, color);   // Left circle
  tft.fillCircle(x + 12, y + 4, 4, color);  // Right circle
  tft.fillTriangle(x, y + 4, x + 8, y + 16, x + 16, y + 4, color); // Bottom triangle

  // Display the heart rate
  tft.setCursor(x + 25, y);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);  
  tft.print("76");  
}

// Draw a bubble icon with SpO2 percentage next to it
void drawBubbleIcon(int x, int y, uint16_t color) {
  tft.drawCircle(x + 8, y + 8, 8, color);    // Outer bubble
  tft.fillCircle(x + 6, y + 6, 2, color);    // Inner highlight

  // Display the sp02 percentage
  tft.setCursor(x + 25, y);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);  
  tft.print("98%");  
}

// Draw a thermometer icon with silver outer and red inner mercury part (in the middle)
void drawThermometerIcon(int x, int y) {
  tft.fillRect(x + 4, y + 2, 4, 12, ST77XX_WHITE); // Thermometer body
  tft.fillCircle(x + 6, y + 16, 3, ST77XX_WHITE);  // Thermometer bottom
  tft.fillRect(x + 5, y + 7, 2, 12, ST77XX_RED); // Mercury in thermometer body
  tft.fillCircle(x + 6, y + 16, 2, ST77XX_RED);// Mercury in thermometer bottom

  //display the body temp
  tft.setCursor(x + 25, y +3);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);  
  tft.print("36.4C");
}

void drawTime(int x, int y, uint16_t color) {
  // Get the current time in milliseconds
  unsigned long currentMillis = millis() + 14000000; //Need RTC module for time
  int minutes = (currentMillis / 60000) % 60;  // Get minutes
  int hours = (currentMillis / 3600000) % 24; // Get hours

  // Display the time in HH:MM format
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(7);
  if (hours < 10) tft.print("0");  // Display leading zero for single-digit hours
  tft.print(hours);
  tft.print(":");
  if (minutes < 10) tft.print("0");  // Display leading zero for single-digit minutes
  tft.print(minutes);
}

void drawDate(int x, int y, uint16_t color) {
  //display date
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(2);
  tft.print("Thu 09/01");
}


// Draw a circular steps gauge
void drawCircularStepsGauge(int x, int y, int steps, int maxSteps, uint16_t color) {
  // Draw the background circle (empty gauge)
  tft.fillCircle(x, y, 50, ST77XX_BLACK);  // Empty gauge background (black color)
  tft.drawCircle(x, y, 50, ST77XX_WHITE); // Draw the border of the circle

  // Calculate the angle based on the steps (angle will range from 0 to 360 degrees)
  int angle = map(steps, 0, maxSteps, 0, 360);  // Map steps to an angle between 0 and 360 degrees

  // Draw the progress (filled arc) using pie slices
  for (int i = 0; i < angle; i++) {
    int x1 = x + 50 * cos(radians(i));  // Calculate the x position
    int y1 = y - 50 * sin(radians(i));  // Calculate the y position
    tft.drawPixel(x1, y1, color);  // Draw the pixel to create the arc
  }

  // Display "Steps" text above the gauge
  tft.setCursor(x - 15, y - 25);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("Steps");

  // Display the step count in the center of the gauge
  tft.setCursor(x - 22, y - 5);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print(steps);  // Display the current step count

  // Display the max steps label below the gauge
  tft.setCursor(x - 15, y + 25);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("/");
  tft.print(maxSteps);  // Display the max steps
}




void drawTemplate() {
  uint8_t padding = 10; // Padding for layout

  // Top Section: Battery level with battery icon
  drawBatteryIcon(padding + 10, padding + 10, ST77XX_WHITE);  // Draw battery icon with 85% charge

  // First Section: Heart Rate and SpO2
  drawHeartIcon(padding + 10, padding + 170, ST77XX_RED);    // Heart icon
  drawBubbleIcon(padding + 10, padding + 240, ST77XX_CYAN); // Bubble icon with SpO2 percentage

  drawCircularStepsGauge(170, 220, 2000, 10000, ST77XX_GREEN);

  // Fourth Section: Body Temperature
  drawThermometerIcon(padding + 10, padding + 200); // Thermometer icon

  drawTime(20, 85, ST77XX_WHITE);

  drawDate(120, 25, ST77XX_WHITE);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println(F("Initializing ST7789 Display..."));

  // Initialize display (240x280 resolution)
  tft.init(240, 280);
  tft.setRotation(2); // Portrait orientation
  tft.fillScreen(ST77XX_BLACK);

  // Set default text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Draw the template
  drawTemplate();
}

void loop() {
  // Continuously update the time every second
  delay(30000);  // Wait for 30 second
  tft.fillScreen(ST77XX_BLACK); //fill the screen black to avoid redundant layers
  drawTemplate();  // Redraw the template to update the time
}
