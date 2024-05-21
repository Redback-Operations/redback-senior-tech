// To Do:
// check the LM35, it not good, or issues arrise, use TMP36, that should work
// add the heart rate sensor
// add the upload data to firebase, all sensor data and rtc
// calibrate clock

// SIT375 Project 2 IOT SubTeam Code for PCB - Elderly Wearable Tech
// Creators: Alex Cojocariu(Lead), Varinder Singh, Vishal Pranau Rama Kumar

/* This is the entire code for the project, using sensors to collect data, 
display on the OLED and send the data to the web */

// libraries
#include <SPI.h> // SPI protocol
#include <WiFiNINA.h> // inbuilt wifi
#include <Adafruit_Sensor.h> // library for the sensors to work
#include <DHT.h> // DHT22 sensor
#include <Adafruit_SSD1306.h> // OLED display
#include <Wire.h> // I2C protocol
#include <Adafruit_BME680.h> // bme680 sensor
#include <Arduino_LSM6DS3.h> // inbuilt accelerometer and gyroscope
#include <RTCZero.h> // inbuilt rtc
#include <WiFiUdp.h> // for getting the current time
#include <NTPClient.h> // for getting the current time
#include <ctime>  // for getting the current time
#include <TimeLib.h> // to set the correct time zone for current time

// Sensor Pins config
#define FLAME_SENSOR_PIN A1
#define TOUCH_SENSOR_PIN 11
#define VIBRATION_SENSOR_PIN 3
#define AMBIENT_LIGHT_SENSOR_PIN A7
#define BUZZER_PIN 2
#define OLED_RESET 4
#define LM35_PIN A6
#define BME680_ADDRESS 0x76 
#define DHT22_PIN 5 

// Sensor Initialization
DHT dht(DHT22_PIN, DHT22);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME680 bme;
RTCZero rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// WiFi and Firebase Configuration
const char* ssid = "SIT374_Project_2_Testing"; // WIFI SSID (change accordingly)
const char* password = "wifi12345"; // WIFI PASSWORD (password accordingly)
const char* firebaseHost = "https://elderlywearable-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* firebaseAuth = "T13IuCe0dn6HwMBzJIhNzXyDv3GjbCxQQo9F0vqo";

// Touch sensor state
bool touched = false;
unsigned long lastTouchTime = 0;
const unsigned long touchDebounceDelay = 50; // Debounce delay in milliseconds

void setup() {
  Serial.begin(9600);

  // begin the sensors   
  pinMode(BUZZER_PIN , OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  dht.begin();
  rtc.begin();
  if (!IMU.begin()) 
  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  if (!bme.begin(BME680_ADDRESS)) 
  {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    display.println("Connecting to WiFi...");
    display.display();
  }

  timeClient.begin();
  timeClient.setPoolServerName("pool.ntp.org"); // Set the NTP server address
  timeClient.setTimeOffset(36000); // +10 hours in seconds for Melbourne Australia
  //int totalOffsetSeconds = (19 * 3600) + (38 * 60); // Calculate the total offset in seconds (19 hours and 38 min)
  //timeClient.setTimeOffset(totalOffsetSeconds); // Set the time offset
}

void loop() {
  int reading = analogRead(LM35_PIN);	// Read Temperature
  float voltage = reading * 3.3 / 1024.0;
  float body_temp = (voltage - 0.5) * 100; // TMP36 linear scale

  float flameValue = analogRead(FLAME_SENSOR_PIN);
  float lightIntensity = analogRead(AMBIENT_LIGHT_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bme.readPressure() / 100.0; // Convert from Pa to hPa
  float gas_resistance = bme.readGas(); // Read gas resistance

  float x, y, z;
  checkVibrations(x, y, z);

  // Check touch sensor state
  bool touchSensorState = digitalRead(TOUCH_SENSOR_PIN);
  unsigned long currentTime = millis();
  if (touchSensorState == HIGH && (currentTime - lastTouchTime) > touchDebounceDelay) {
    touched = !touched; // Toggle touched state
    lastTouchTime = currentTime;
  }

  // Display either of the 2 different screens on the 1 OLED
  if (touched) {
    DisplayTime_HeartRate();
  } else {
    DisplaySensorData(temperature, humidity, pressure, gas_resistance, lightIntensity, body_temp, flameValue);
  }
  
  // checks for emergency and safety
  if (flameValue > 1000)
  {
    touched = false;
    Display("FIRE!");
    tone(BUZZER_PIN, 85);
    delay(2000);
  }
  if (gas_resistance < 2000)
  { 
    touched = false;
    Display("BAD AIR QUALITY");
    tone(BUZZER_PIN, 85);
    delay(2000);
  }
}

void checkVibrations(float &x, float &y, float &z) {
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(x, y, z);
    if (abs(x) > 2.0 || abs(y) > 2.0 || abs(z) > 2.0) //sound if acceleration exceeds a threshold (2g(s)) in any axis
    { 
      touched = false;
      Display("SHOCK!");
      tone(BUZZER_PIN, 85);
      delay(1000);
    }
  }
  if (IMU.gyroscopeAvailable()) 
  {
    IMU.readGyroscope(x, y, z);
    if (abs(x) > 100.0 || abs(y) > 100.0 || abs(z) > 100.0) // sound if angular velocity exceeds a threshold (100 deg/s) in any axis
    { 
      touched = false;
      Display("SHOCK!");
      tone(BUZZER_PIN, 85);
      delay(1000);
    }
  }
}

void DisplayTime_HeartRate() {
  display.clearDisplay();
  int16_t x, y;
  uint16_t width, height;
  timeClient.update(); // Get the current time from the NTP server
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm* ptm = localtime((time_t*)&epochTime);
  int hours = ptm->tm_hour;
  int minutes = ptm->tm_min;
  int seconds = ptm->tm_sec;
  // Determine AM or PM
  String amPm = "AM";
  if (hours >= 12) 
  {
    amPm = "PM";
    if (hours > 12) 
    {
      hours -= 12; // Convert to 12-hour format
    }
  } 
  else if (hours == 0) 
  {
    hours = 12; // Handle 0 as 12 AM
  }
  String timeString = String(hours) + ":" + String(minutes) + ":" + String(seconds) + " " + amPm; // Format the time string with AM/PM
  display.setTextSize(2);
  display.getTextBounds(timeString, 0, 0, &x, &y, &width, &height); // Calculate the X and Y coordinates to center the text
  x = (SCREEN_WIDTH - width) / 2;
  y = (SCREEN_HEIGHT - height) / 2;
  display.setCursor(x, y); // Set the cursor position
  display.print(timeString);
  display.display(); // Update the display
}

// display text in the center of the oled display
void Display(String text) {
  display.clearDisplay(); 
  int16_t x, y;
  uint16_t width, height;
  display.setTextSize(3);
  display.getTextBounds(text, 0, 0, &x, &y, &width, &height); // Calculate the X and Y coordinates to center the text
  x = (SCREEN_WIDTH - width) / 2;
  y = (SCREEN_HEIGHT - height) / 2;
  display.setCursor(x, y); // Set the cursor position
  display.print(text);
  display.display(); // Update the display
}

void DisplaySensorData(float temperature, float humidity, float pressure, float gas_resistance, float lightIntensity, float body_temp, float flameValue) {
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Humidity: "); display.print(humidity); display.println(" %");
  display.print("Pressure: "); display.print(pressure); display.println(" hPa");
  display.print("Gas: "); display.print(gas_resistance); display.println(" ohms");
  display.print("Light: "); display.print(lightIntensity); display.println(" lux");
  display.print("Body Temp: "); display.print(body_temp); display.println(" C");
  if (flameValue < 1000)
  {
    display.print("No Fire Detected");
    noTone(BUZZER_PIN);
  }
  display.println(""); // space needed
  if (gas_resistance > 2000)
  {
    display.print("Good Air Quality");
    noTone(BUZZER_PIN);
  }
  display.display();
  //display.print("Heart Rate: "); display.print(heartRate); display.println(" bpm");
}
