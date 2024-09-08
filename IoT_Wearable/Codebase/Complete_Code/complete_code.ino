// SIT375 Project 2 IOT SubTeam Code for PCB - Elderly Wearable Tech
// Creators: Alex Cojocariu(Lead), Varinder Singh, Vishal Pranau Rama Kumar

/* This is the entire code for the project, using sensors to collect data, 
display on the OLED and send the data to the cloud (Thingspeak) */

#include "secrets.h" // houses the wifi and thingspeak credentals

// libraries
#include <SPI.h> // SPI protocol
#include <WiFiNINA.h> // inbuilt wifi
#include <Adafruit_Sensor.h> // library for the sensors to work
#include <DHT.h> // DHT22 sensor
#include <Adafruit_GFX.h> // for OLED display
#include <Adafruit_SSD1306.h> // OLED display
#include <Wire.h> // I2C protocol
#include <Adafruit_BME680.h> // bme680 sensor
#include <Arduino_LSM6DS3.h> // inbuilt accelerometer and gyroscope
#include <RTCZero.h> // inbuilt rtc
#include <WiFiUdp.h> // for getting the current time
#include <DFRobot_MAX30102.h> // for the heart rate and spo2 sensor
#include "ThingSpeak.h" // for uploading the data to the cloud

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
DFRobot_MAX30102 particleSensor;
RTCZero rtc;
int status = WL_IDLE_STATUS;
const int GMT = +10;// Time zone constant (Melbourne Australia)

// WiFi and thingspeak Configuration
WiFiClient  client;
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
// need 2 channels 
unsigned long myChannelNumber1 = SECRET_CH_ID_1;
const char * myWriteAPIKey1 = SECRET_WRITE_APIKEY_1;
unsigned long myChannelNumber2 = SECRET_CH_ID_2;
const char * myWriteAPIKey2 = SECRET_WRITE_APIKEY_2;

// variables to keep track of the last time of data upload
unsigned long lastUploadTime = 0;
unsigned long uploadInterval = 5000; // Upload every 5 seconds

// variables for scrolling through display information
bool touchSensorState = false;
unsigned long lastTouchTime = 0;
const unsigned long touchDebounceDelay = 50; // Debounce delay in milliseconds
const int numScreens = 3;
int currentScreenIndex = 0; // Current screen index

int32_t SPO2; //SPO2
int8_t SPO2Valid; //Flag to display if SPO2 calculation is valid
int32_t heartRate; //Heart-rate
int8_t heartRateValid; //Flag to display if heart-rate calculation is valid 

int flameValueThreshold = 390;
int gasResistanceThreshold = 2000;

void setup() {
  Serial.begin(9600);

  // begin the sensors and libraries  
  pinMode(BUZZER_PIN , OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  dht.begin();
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
  while (!particleSensor.begin()) 
  {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }
  particleSensor.sensorConfiguration(/*ledBrightness=*/50, /*sampleAverage=*/SAMPLEAVG_4, /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_200, /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Establish a WiFi connection
  while (status != WL_CONNECTED) {
    display.println("Connecting to WiFi...");
    display.display();
    status = WiFi.begin(ssid, password);
    delay(10000); // Wait 10 seconds for connection
  }

  rtc.begin(); // Start Real Time Clock
  unsigned long epoch; // Variable for epoch
  int numberOfTries = 0, maxTries = 6; // Variable for number of tries to NTP service
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
  ThingSpeak.begin(client);  // Initialize ThingSpeak 
}

void loop() {
  float body_temp = bme.readTemperature() + 10;
  float flameValue = analogRead(FLAME_SENSOR_PIN);
  float lightIntensity = analogRead(AMBIENT_LIGHT_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bme.readPressure() / 100.0; // Convert from Pa to hPa
  float gas_resistance = bme.readGas(); // Read gas resistance
  particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);

  float x, y, z;
  checkVibrations(x, y, z);

  // Check touch sensor state
  bool touchSensorState = digitalRead(TOUCH_SENSOR_PIN);
  unsigned long currentTime = millis();
  if (touchSensorState == HIGH && (currentTime - lastTouchTime) > touchDebounceDelay) {
    // Increment the current screen index
    currentScreenIndex = (currentScreenIndex + 1) % numScreens;
    lastTouchTime = currentTime;
  }

  // Display either of the 3 different screens on the 1 OLED
  // Display the appropriate screen based on the current index
  switch (currentScreenIndex) 
  {
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
  // checks for emergency and safety
  if (flameValue > flameValueThreshold)
  {
    touchSensorState = false;
    Display("FIRE!");
    tone(BUZZER_PIN, 85);
    delay(2000);
  }
  if (gas_resistance < gasResistanceThreshold)
  { 
    touchSensorState = false;
    Display("BAD AIR QUALITY");
    tone(BUZZER_PIN, 85);
    delay(2000);
  }

  // Upload data to ThingSpeak without delaying the rest of the code every 10 seconds
  unsigned long currentTime_Upload = millis(); // Get the current time for code execution
  if (currentTime_Upload - lastUploadTime >= uploadInterval) 
  {
    uint32_t timestamp = rtc.getEpoch();
    // set the fields of the sensor data and write to thingspeak channel
    ThingSpeak.setField(1, (long)timestamp); // in seconds
    ThingSpeak.setField(2, body_temp);
    ThingSpeak.setField(3, flameValue);
    ThingSpeak.setField(4, lightIntensity);
    ThingSpeak.setField(5, pressure);
    ThingSpeak.setField(6, gas_resistance);
    ThingSpeak.setField(7, temperature);
    ThingSpeak.setField(8, humidity);
    ThingSpeak.writeFields(myChannelNumber1, myWriteAPIKey1);
    ThingSpeak.setField(1, (long)timestamp); // in seconds
    ThingSpeak.setField(2, heartRate);
    ThingSpeak.setField(3, SPO2);
    ThingSpeak.writeFields(myChannelNumber2, myWriteAPIKey2); 
    lastUploadTime = currentTime_Upload;
  }
}

void checkVibrations(float &x, float &y, float &z) {
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(x, y, z);
    if (abs(x) > 2.0 || abs(y) > 2.0 || abs(z) > 2.0) //sound if acceleration exceeds a threshold (2g(s)) in any axis
    { 
      touchSensorState = false;
      Display("SHOCK!");
      tone(BUZZER_PIN, 85);
      delay(1000);
      noTone(BUZZER_PIN);
    }
  }
  if (IMU.gyroscopeAvailable()) 
  {
    IMU.readGyroscope(x, y, z);
    if (abs(x) > 100.0 || abs(y) > 100.0 || abs(z) > 100.0) // sound if angular velocity exceeds a threshold (100 deg/s) in any axis
    { 
      touchSensorState = false;
      Display("SHOCK!");
      tone(BUZZER_PIN, 85);
      delay(1000);
      noTone(BUZZER_PIN);
    }
  }
}

void DisplayTime() {
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

  // for displaying the date and time in a nice way
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
  if (flameValue < flameValueThreshold)
  {
    display.print("No Fire Detected");
    noTone(BUZZER_PIN);
  }
  display.println(""); // space needed
  if (gas_resistance > gasResistanceThreshold)
  {
    display.print("Good Air Quality");
    noTone(BUZZER_PIN);
  }
  display.display();
}

void DisplayHeartData(int32_t SPO2, int32_t heartRate) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  // Display heart rate
  display.setCursor(0,0);
  display.print("Heart Rate: ");
  display.print(heartRate);
  display.println(" BPM");
  
  // Display SpO2
  display.setCursor(0,20);
  display.print("SPO2: ");
  display.print(SPO2);
  display.println(" Oxygen %");
  
  // Display more info
  display.setCursor(0,40);
  display.println("Normal HR: 60-100 BPM");
  display.println("Normal SPO2: 95-100%");
  display.display();
}
