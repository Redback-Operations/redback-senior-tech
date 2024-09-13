/*
  Arduino Nano 33 IoT WiFi RTC Demo with OLED Display
  Demonstrates use of Real Time Clock and OLED display
  Gets Linux epoch from network NTP service and determines current time
  Results on OLED display
*/

// Include required libraries
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi Credentials (edit as required)
char ssid[] = "SIT374_Project_2_Testing";      // Wifi SSID
char pass[] = "wifi12345";       // Wifi password

// Object for Real Time Clock
RTCZero rtc;

// Object for OLED display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int status = WL_IDLE_STATUS;

const int GMT = +10;// Time zone constant - change as required for your location

void setup() {
  Serial.begin(9600);

  // Check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    // Wait until WiFi ready
    Serial.println("WiFi adapter not ready");
    while (true);
  }

  // Establish a WiFi connection
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(10000);
  }

  // Start Real Time Clock
  rtc.begin();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  // Variable to represent epoch
  unsigned long epoch;

  // Variable for number of tries to NTP service
  int numberOfTries = 0, maxTries = 6;

  do 
  {
    epoch = WiFi.getTime(); // Get epoch
    numberOfTries++;
  }
  while ((epoch == 0) && (numberOfTries < maxTries));
    if (numberOfTries == maxTries) 
    {
      display.println("NTP unreachable!!");
      while (1);
    }
    else 
    {
      display.print("Epoch received: ");
      display.println(epoch);
      rtc.setEpoch(epoch);
    }
}

void loop() {
  display.clearDisplay();
  
  // Extract date and time components
  int year = rtc.getYear();
  int month = rtc.getMonth();
  int day = rtc.getDay();
  int hours = rtc.getHours() + GMT;
  int minutes = rtc.getMinutes();
  int seconds = rtc.getSeconds();
  String amPm;

  // Determine AM/PM
  if ((rtc.getHours() + GMT) < 12) {
    amPm = "AM";
  } else {
    amPm = "PM";
  }

  // Format the date and time strings
  String dateString = String(day) + "/" + String(month) + "/" + String(year);
  String timeString = String(hours) + ":" + String(minutes) + ":" + String(seconds) + amPm;

  int16_t x, y;
  uint16_t width, height;
  display.setTextSize(2);
  display.getTextBounds(dateString, 0, 0, &x, &y, &width, &height); // Calculate the X and Y coordinates to center the text
  x = (SCREEN_WIDTH - width) / 2;
  y = (SCREEN_HEIGHT - height) / 2;
  display.setCursor(x, y); // Set the cursor position
  display.println(dateString);
  display.println(timeString);
  display.display(); // Update the display
}
