// Credit - https://circuitdigest.com/microcontroller-projects/interface-dht22-sensor-module-with-arduino

/*
More Resource Links - 
  https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
  https://lastminuteengineers.com/dht11-dht22-arduino-tutorial/
  https://arduinogetstarted.com/tutorials/arduino-dht22
  https://www.makerguides.com/dht11-dht22-arduino-tutorial/
  

*/

#include <Wire.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void setup()
{
    Serial.begin(115200);

    pinMode(DHTPin, INPUT);

    dht.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.display();

    delay(100);

    display.clearDisplay();

    display.display();

    display.setTextSize(1.75);

    display.setTextColor(WHITE);
}

void loop()
{

    Humidity = dht.readHumidity();

    // Read temperature as Celsius (the default)

    Temperature = dht.readTemperature();

    // Read temperature as Fahrenheit (isFahrenheit = true)

    Temp_Fahrenheit = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).

    if (isnan(Humidity) || isnan(Temperature) || isnan(Temp_Fahrenheit))
    {

        Serial.println(F("Failed to read from DHT sensor!"));

        return;
    }

    Serial.print(F("Humidity: "));

    Serial.print(Humidity);

    Serial.print(F("%  Temperature: "));

    Serial.print(Temperature);

    Serial.print(F("°C "));

    Serial.print(Temp_Fahrenheit);

    Serial.println(F("°F "));

    display.setCursor(0, 0);

    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);

    display.print("Temperature: ");

    display.setTextSize(2);

    display.setCursor(0, 10);

    display.print(Temperature);

    display.print(" ");

    display.setTextSize(1);

    display.cp437(true);

    display.write(167);

    display.setTextSize(2);

    display.print("C");

    display.setTextSize(1);

    display.setCursor(0, 35);

    display.print("Humidity: ");

    display.setTextSize(2);

    display.setCursor(0, 45);

    display.print(Humidity);

    display.print(" %");

    display.display();

    delay(1000);
}