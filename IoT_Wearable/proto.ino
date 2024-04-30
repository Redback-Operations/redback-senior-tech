#include <SPI.h>
#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>               // All the libraries that we will be Using
#include <Adafruit_MAX30105.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <FirebaseArduino.h>

// Sensor Pins config will change according to the connection on the prototype 
#define FLAME_SENSOR_PIN A0
#define GAS_SENSOR_PIN A1
#define TOUCH_SENSOR_PIN A2
#define VIBRATION_SENSOR_PIN A3
#define AMBIENT_LIGHT_SENSOR_PIN A4
#define BUZZER_PIN 2
#define OLED_RESET 4
#define LM35_PIN A5
#define HEART_RATE_PIN A6

// Sensor Initialization
DHT dht(7, DHT22);
Adafruit_MAX30105 maxSensor;
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// WiFi and Firebase Configuration (In process of creating a New Firebase)
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* firebaseHost = "your-firebase-app.firebaseio.com";
const char* firebaseAuth = "your_firebase_database_secret";

// Sensor Reading Functions
float readTemperatureLM35() {
    int analogValue = analogRead(LM35_PIN);
    float voltage = (analogValue / 1023.0) * 3300; // convert to millivolts
    float temperatureC = voltage / 10.0; // 10.0 mV per degree Celsius
    return temperatureC;
}

void setup() {
    Serial.begin(115200); 
    dht.begin();
    maxSensor.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);                     // Display Setup
    display.setTextColor(WHITE);
    display.display();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);                               // WIFI Setup
        display.println("Connecting to WiFi...");
        display.display();
    }
    Firebase.begin(firebaseHost, firebaseAuth);
}

void loop() {
    float flameValue = analogRead(FLAME_SENSOR_PIN);
    float gasValue = analogRead(GAS_SENSOR_PIN);
    float lightIntensity = analogRead(AMBIENT_LIGHT_SENSOR_PIN);
    float temperatureC = readTemperatureLM35();
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float heartRate = maxSensor.getHeartRate(); 

    if (flameValue > 300) digitalWrite(BUZZER_PIN, HIGH); //Buzzer functionalities for Flame sensor 
    else digitalWrite(BUZZER_PIN, LOW);

    if (gasValue > 400) digitalWrite(BUZZER_PIN, HIGH);//Buzzer functionalities for alerting incase of CO2 levels beyond threshold

    display.clearDisplay();//Displaying the data on the OLED screen
    display.setCursor(0,0);
    display.print("Temp: "); display.print(temperature); display.println(" C");
    display.print("Humidity: "); display.print(humidity); display.println(" %");
    display.print("Heart Rate: "); display.print(heartRate); display.println(" bpm");
    display.print("Light: "); display.print(lightIntensity);
    display.display();

    if (lightIntensity < 300) display.dim(true); // Dims the OLED acoording to ambience
    else display.dim(false);

    Firebase.pushFloat("temperature", temperature);
    Firebase.pushFloat("humidity", humidity);
    Firebase.pushFloat("heartRate", heartRate);
    Firebase.pushFloat("lightIntensity", lightIntensity);

    delay(2000);
}
