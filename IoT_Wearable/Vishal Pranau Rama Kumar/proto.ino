//to add, heart rate senor code , LM35, connection to firebase with timestamp(rtc) , digital vibrations sensors sould activate buzzer, revmove the lightsensor code that changes the backlight, it should be removed
                                                                                        // if that doesnt work use inbuilt accelerometer and gyroscope to do it.
                                                                                    

#include <SPI.h>
#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DFRobot_MAX30102.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_BME680.h>  // Include the BME680 library
#include <RTCZero.h>
#include <WiFiUdp.h>
//#include <FirebaseArduino.h>  // Include the Firebase Arduino library

// Sensor Pins config
#define FLAME_SENSOR_PIN A1
#define TOUCH_SENSOR_PIN D11
#define VIBRATION_SENSOR_PIN D3
#define AMBIENT_LIGHT_SENSOR_PIN A7
#define BUZZER_PIN 2
#define OLED_RESET 4
#define LM35_PIN A6
#define BME680_ADDRESS 0x76 
#define DHT22_PIN 5 

RTCZero rtc;

// Sensor Initialization
DHT dht(DHT22_PIN, DHT22);
DFRobot_MAX30102 maxSensor;
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
Adafruit_BME680 bme; // Create an instance of the Adafruit BME680 class

// WiFi and Firebase Configuration
const char* ssid = "One";//Change WIFI SSID to your specification
const char* password = "wifi12345";//Change password accordingly
const char* firebaseHost = "https://elderlywearable-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* firebaseAuth = "T13IuCe0dn6HwMBzJIhNzXyDv3GjbCxQQo9F0vqo";

int status = WL_IDLE_STATUS;
 
// Time zone constant - change as required for your location
const int GMT = 9; // 9 for australia 

void print2digits(int number) {
 
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}
 
void printTime()
{
 
  print2digits(rtc.getHours() + GMT);
  Serial.print(":");
  
  print2digits(rtc.getMinutes());
  Serial.print(":");
  
  print2digits(rtc.getSeconds());
  Serial.println();
}
 
void printDate()
{
 
  Serial.print(rtc.getDay());
  Serial.print("/");
  
  Serial.print(rtc.getMonth());
  Serial.print("/");
  
  Serial.print(rtc.getYear());
  Serial.print(" ");
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    maxSensor.begin();

    if (!bme.begin(BME680_ADDRESS)) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        while (1);
    }

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    pinMode(BUZZER_PIN , OUTPUT);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        display.println("Connecting to WiFi...");
        display.display();
    }
    //Firebase.begin(firebaseHost, firebaseAuth);

    rtc.begin();
  
  // Variable to represent epoch
  unsigned long epoch;
 
 // Variable for number of tries to NTP service
  int numberOfTries = 0, maxTries = 6;
 
 // Get epoch
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
 
  while ((epoch == 0) && (numberOfTries < maxTries));
 
    if (numberOfTries == maxTries) {
    Serial.print("NTP unreachable!!");
    while (1);
    }
 
    else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);
    Serial.println();
    }

}


void loop() {
    float flameValue = analogRead(FLAME_SENSOR_PIN);
    float lightIntensity = analogRead(AMBIENT_LIGHT_SENSOR_PIN);
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0; // Convert from Pa to hPa
    float gas_resistance = bme.readGas(); // Read gas resistance
    //float heartRate = maxSensor.getHeartRate();

    display.clearDisplay(); // Displaying the data on the OLED screen
    display.setCursor(0,0);
    display.print("Temp: "); display.print(temperature); display.println(" C");
    display.print("Humidity: "); display.print(humidity); display.println(" %");
    display.print("Pressure: "); display.print(pressure); display.println(" hPa");
    display.print("Gas: "); display.print(gas_resistance); display.println(" ohms");
    //display.print("Heart Rate: "); display.print(heartRate); display.println(" bpm");
    display.print("Light: "); display.print(lightIntensity); display.println(" lux");
    display.println("");
    if (flameValue > 1110)
    {
      display.print("FIRE , FIRE , FIRE");
      tone(BUZZER_PIN,85);
    }
    else 
    {
      display.print("No Flames Detected");
      noTone(BUZZER_PIN);
    }
    display.println("");
    if(gas_resistance < 2000)
    {
      display.print("BAD AIR QUALITY");
      tone(BUZZER_PIN,85);
    }
    else 
    {
      display.print("AIR QUALITY IS GOOD");
      noTone(BUZZER_PIN);
    }
    
    display.display();

    display.dim(lightIntensity < 300);

    // Construct JSON data
    String jsonData = "{";
    jsonData += "\"temperature\":" + String(temperature) + ",";
    jsonData += "\"humidity\":" + String(humidity) + ",";
    jsonData += "\"pressure\":" + String(pressure) + ",";
    jsonData += "\"gas_resistance\":" + String(gas_resistance) + ",";
    //jsonData += "\"heartRate\":" + String(heartRate) + ",";
    jsonData += "\"lightIntensity\":" + String(lightIntensity);
    jsonData += "}";

    // Push JSON data to Firebase
    //Firebase.pushJSON("/sensor_data", jsonData.c_str());

    delay(2000);
}
