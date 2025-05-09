#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// WiFi Credentials (edit as required)
char ssid[] = "iPhone";
char pass[] = "wifi12345";

// Object for Real Time Clock
RTCZero rtc;

// Object for ST7789 display
#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         7
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 280

int status = WL_IDLE_STATUS;

const int GMT = +10; // Time zone constant

void setup() {
  Serial.begin(9600);

  // Check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi adapter not ready");
    while (true);
  }

  // Establish a WiFi connection
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  // Start Real Time Clock
  rtc.begin();

  // Initialize ST7789 display
  tft.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);

  // Get epoch time
  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;

  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  } while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {
    tft.println("NTP unreachable!!");
    while (1);
  } else {
    rtc.setEpoch(epoch);
  }
}

void loop() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Extract date and time components
  int year = rtc.getYear() + 2000; // Adjust year to display as 2024 instead of 0024
  int month = rtc.getMonth();
  int day = rtc.getDay();
  int hours = (rtc.getHours() + GMT) % 24;
  int minutes = rtc.getMinutes();
  int seconds = rtc.getSeconds();
  String amPm = (hours < 12) ? "AM" : "PM";

  // Convert to 12-hour format
  hours = (hours > 12) ? hours - 12 : hours;
  hours = (hours == 0) ? 12 : hours;

  // Format the date and time strings
  char dateString[20];
  char timeString[20];
  sprintf(dateString, "%02d/%02d/%04d", day, month, year); // Year is now 4 digits
  sprintf(timeString, "%02d:%02d:%02d %s", hours, minutes, seconds, amPm.c_str());

  // Display date
  tft.setTextSize(3);
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT / 2) - h - 10);
  tft.println(dateString);

  // Display time
  tft.setTextSize(3);
  tft.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT / 2) + 10);
  tft.println(timeString);

  delay(1000); // Update every second
}
