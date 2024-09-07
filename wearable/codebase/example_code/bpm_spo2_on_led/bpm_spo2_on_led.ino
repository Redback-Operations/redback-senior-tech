#include <DFRobot_MAX30102.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

DFRobot_MAX30102 particleSensor;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  //Init serial
  Serial.begin(115200);
  while (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }

  particleSensor.sensorConfiguration(/*ledBrightness=*/50, /*sampleAverage=*/SAMPLEAVG_4, /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_200, /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

int32_t SPO2; //SPO2
int8_t SPO2Valid; //Flag to display if SPO2 calculation is valid
int32_t heartRate; //Heart-rate
int8_t heartRateValid; //Flag to display if heart-rate calculation is valid 

void loop()
{
  particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);
  
  display.clearDisplay();
  
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
  
  display.display();
}
