#include <SPI.h> // SPI protocol
#include <WiFiNINA.h> // inbuilt wifi
#include <Adafruit_Sensor.h> // library for the sensors to work
#include <DHT.h> // DHT22 sensor
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ST7789.h> // ST7789 TFT display library
#include <Wire.h> // I2C protocol
#include <Adafruit_BME680.h> // bme680 sensor
#include <Arduino_LSM6DS3.h> // inbuilt accelerometer and gyroscope
#include <RTCZero.h> // inbuilt rtc
#include <WiFiUdp.h> // for getting the current time
#include <DFRobot_MAX30102.h> // for the heart rate and spo2 sensor
#include <Firebase_Arduino_WiFiNINA.h> // Firebase library for WiFiNINA

// Sensor Pins config
#define FLAME_SENSOR_PIN A1
#define TOUCH_SENSOR_PIN 11
#define VIBRATION_SENSOR_PIN 3
#define AMBIENT_LIGHT_SENSOR_PIN A7
#define BUZZER_PIN 2
#define LM35_PIN A6
#define BME680_ADDRESS 0x76 
#define DHT22_PIN 5 

// LCD Pins config
#define TFT_CS     10 // Chip select control pin
#define TFT_RST    8  // Reset pin
#define TFT_DC     9  // Data/command control pin

// Initialize ST7789 display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Sensor Initialization
DHT dht(DHT22_PIN, DHT22);
Adafruit_BME680 bme;
DFRobot_MAX30102 particleSensor;
RTCZero rtc;
int status = WL_IDLE_STATUS;
const int GMT = +10; // Time zone constant (Melbourne, Australia)

// WiFi and Firebase Configuration
WiFiClient  client;
FirebaseData firebaseData;
const char* ssid = "insert wifi ssid here";
const char* password = "insert wifi password here";
const char* firebaseHost = "Add Firebase Host here";
const char* firebaseAuth = "Add Firebase Auth here";

// variables to keep track of the last time of data upload
unsigned long lastUploadTime = 0;
unsigned long uploadInterval = 5000; // Upload every 5 seconds

// variables for scrolling through display information
bool touchSensorState = false;
unsigned long lastTouchTime = 0;
const unsigned long touchDebounceDelay = 50; // Debounce delay in milliseconds
const int numScreens = 3;
int currentScreenIndex = 0; // Current screen index

int32_t SPO2; // SPO2
int8_t SPO2Valid; // Flag to display if SPO2 calculation is valid
int32_t heartRate; // Heart-rate
int8_t heartRateValid; // Flag to display if heart-rate calculation is valid 

int flameValueThreshold = 390;
int gasResistanceThreshold = 2000;

void setup() {
  Serial.begin(9600);

  // Initialize the TFT display
  tft.init(240, 280); // Initialize ST7789 display (240x280 resolution)
  tft.setRotation(1); // Set rotation for the screen
  tft.fillScreen(ST77XX_BLACK); // Clear the display with black background
  tft.setTextColor(ST77XX_WHITE); // Set text color

  // Begin the sensors and libraries
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  dht.begin();
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  if (!bme.begin(BME680_ADDRESS)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  while (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }
  particleSensor.sensorConfiguration(50, SAMPLEAVG_4, MODE_MULTILED, SAMPLERATE_200, PULSEWIDTH_411, ADCRANGE_16384);

  // Establish a WiFi connection
  while (status != WL_CONNECTED) {
    tft.setCursor(20, 120);
    tft.setTextSize(2);
    tft.print("Connecting to WiFi...");
    status = WiFi.begin(ssid, password);
    delay(10000); // Wait 10 seconds for connection
  }

  rtc.begin(); // Start Real Time Clock
  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;
  do {
    epoch = WiFi.getTime(); // Get epoch
    numberOfTries++;
  } while ((epoch == 0) && (numberOfTries < maxTries));
  
  if (numberOfTries == maxTries) {
    tft.setCursor(10, 120);
    tft.setTextSize(2);
    tft.print("NTP unreachable!!");
    while (1);
  } else {
    rtc.setEpoch(epoch);
  }

  // Initialize Firebase
  Firebase.begin(firebaseHost, firebaseAuth, ssid, password);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float body_temp = bme.readTemperature() + 10;
  float flameValue = analogRead(FLAME_SENSOR_PIN);
  float lightIntensity = analogRead(AMBIENT_LIGHT_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bme.readPressure() / 100.0; // Convert from Pa to hPa
  float gas_resistance = bme.readGas(); // Read gas resistance
  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);

  float x, y, z;
  checkVibrations(x, y, z);

  bool touchSensorState = digitalRead(TOUCH_SENSOR_PIN);
  unsigned long currentTime = millis();
  if (touchSensorState == HIGH && (currentTime - lastTouchTime) > touchDebounceDelay) {
    currentScreenIndex = (currentScreenIndex + 1) % numScreens;
    lastTouchTime = currentTime;
  }

  switch (currentScreenIndex) {
    case 0:
      DisplayTime();
      break;
    case 1:
      DisplaySensorData(temperature, humidity, pressure, gas_resistance, lightIntensity, body_temp, flameValue);
      break;
    case 2:
      DisplayHeartData(SPO2, heartRate);
      break;
  }

  if (flameValue > flameValueThreshold) {
    touchSensorState = false;
    DisplayWarning("FIRE!");
  }
  if (gas_resistance < gasResistanceThreshold) {
    touchSensorState = false;
    DisplayWarning("BAD AIR QUALITY");
  }

  unsigned long currentTime_Upload = millis();
  if (currentTime_Upload - lastUploadTime >= uploadInterval) {
    uint32_t timestamp = rtc.getEpoch();
    Firebase.setInt(firebaseData, "/sensorData/timestamp", timestamp);
    Firebase.setFloat(firebaseData, "/sensorData/body_temp", body_temp);
    Firebase.setFloat(firebaseData, "/sensorData/flameValue", flameValue);
    Firebase.setFloat(firebaseData, "/sensorData/lightIntensity", lightIntensity);
    Firebase.setFloat(firebaseData, "/sensorData/pressure", pressure);
    Firebase.setFloat(firebaseData, "/sensorData/gas_resistance", gas_resistance);
    Firebase.setFloat(firebaseData, "/sensorData/temperature", temperature);
    Firebase.setFloat(firebaseData, "/sensorData/humidity", humidity);
    Firebase.setInt(firebaseData, "/heartData/heartRate", heartRate);
    Firebase.setInt(firebaseData, "/heartData/SPO2", SPO2);

    if (firebaseData.dataAvailable()) {
      Serial.println("Data uploaded successfully");
    } else {
      Serial.println("Data upload failed: " + firebaseData.errorReason());
    }
    lastUploadTime = currentTime_Upload;
  }
}

void checkVibrations(float &x, float &y, float &z) {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    if (abs(x) > 2.0 || abs(y) > 2.0 || abs(z) > 2.0) {
      touchSensorState = false;
      DisplayWarning("SHOCK!");
    }
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    if (abs(x) > 100.0 || abs(y) > 100.0 || abs(z) > 100.0) {
      touchSensorState = false;
      DisplayWarning("SHOCK!");
    }
  }
}

void DisplayTime() {
  // Draw gradient background
  drawGradientBackground(); 

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  
  int year = rtc.getYear();
  int month = rtc.getMonth();
  int day = rtc.getDay();
  int hours = rtc.getHours() + GMT;

  if (hours >= 24) {
    hours -= 24;
    day++;
  }

  int minutes = rtc.getMinutes();
  int seconds = rtc.getSeconds();
  String amPm = (hours < 12) ? "AM" : "PM";

  if (hours > 12) {
    hours -= 12;
  }
  if (hours == 0) {
    hours = 12;
  }

  String dateString = String(day) + "/" + String(month) + "/" + String(year);
  String timeString = String(hours) + ":" + String(minutes) + ":" + String(seconds) + " " + amPm;

  tft.setCursor(10, 50);
  tft.print("Date: ");
  tft.print(dateString);
  
  tft.setCursor(10, 100);
  tft.print("Time: ");
  tft.print(timeString);
}

void DisplaySensorData(float temperature, float humidity, float pressure, float gas_resistance, float lightIntensity, float body_temp, float flameValue) {
  // Draw gradient background
  drawGradientBackground(); 

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  
  tft.setCursor(10, 20);
  tft.print("Temp: "); tft.print(temperature); tft.println(" C");
  tft.setCursor(10, 40);
  tft.print("Humidity: "); tft.print(humidity); tft.println(" %");
  tft.setCursor(10, 60);
  tft.print("Pressure: "); tft.print(pressure); tft.println(" hPa");
  tft.setCursor(10, 80);
  tft.print("Gas: "); tft.print(gas_resistance); tft.println(" ohms");
  tft.setCursor(10, 100);
  tft.print("Light: "); tft.print(lightIntensity); tft.println(" lux");
  tft.setCursor(10, 120);
  tft.print("Body Temp: "); tft.print(body_temp); tft.println(" C");

  if (flameValue < flameValueThreshold) {
    tft.setCursor(10, 140);
    tft.print("No Fire Detected");
  }

  if (gas_resistance > gasResistanceThreshold) {
    tft.setCursor(10, 160);
    tft.print("Good Air Quality");
  }
}

void DisplayHeartData(int32_t SPO2, int32_t heartRate) {
  // Draw gradient background
  drawGradientBackground(); 

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(10, 50);
  tft.print("Heart Rate: ");
  tft.print(heartRate);
  tft.println(" BPM");

  tft.setCursor(10, 100);
  tft.print("SPO2: ");
  tft.print(SPO2);
  tft.println(" %");
  
  tft.setCursor(10, 150);
  tft.println("Normal HR: 60-100 BPM");
  tft.println("Normal SPO2: 95-100%");
}

void DisplayWarning(String message) {
  tft.fillScreen(ST77XX_RED);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(20, 120);
  tft.print(message);
}

// Function to create a simple gradient background
void drawGradientBackground() {
  uint16_t color;
  
  for (int y = 0; y < 240; y++) {
    // Create a color gradient from red to blue
    color = tft.color565(y, 0, 255 - y);  // Red -> Blue gradient
    tft.drawFastHLine(0, y, 280, color);  // Draw a horizontal line of this color
  }
}
