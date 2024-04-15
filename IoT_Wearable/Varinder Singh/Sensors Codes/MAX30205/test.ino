/*
 * This program Print temperature on 3, 7segment display
 * Hardware Connections (Breakoutboard to Arduino Nano):
 * Vin  - 5V (3.3V is allowed)
 * GND - GND
 * MAX30205 SDA - A4
 * MAX30205 SCL - A5
 * 74HC595 ST_CP - D5
 * 74HC595 SH_CP - D6
 * 74HC595 DS - D7
 * 
 * 
 * Credit - https://circuitdigest.com/microcontroller-projects/arduino-max30205-human-body-temperature-measurement
 * 
 */



#include <Wire.h>
#include "Protocentral_MAX30205.h" // Arduino Contributed Libs (https://github.com/protocentral/ProtoCentral_MAX30205)
// define MAX30205 objectData
MAX30205 tempSensor;
// Show the temperature in Fahrenheit 
const bool fahrenheittemp = true; // I'm showing the temperature in Fahrenheit, If you want to show the temperature in Celsius then make this variable false.
// set the 7segment type (common Cathode or Anode)
const bool commonCathode = true; // I'm using common Cathode 7segment if you use common Anode then change the value into false.
// alpha-digit pattern for a 7-segment display
const byte digit_pattern[17] =
{
  // 74HC595 Output Connection with 7segment display.
  // Q0 Q1 Q2 Q3 Q4 Q5 Q6 Q7
  // a  b  c  d  e  f  g  DP
  0b11111100,  // 0
  0b01100000,  // 1
  0b11011010,  // 2
  0b11110010,  // 3
  0b01100110,  // 4
  0b10110110,  // 5
  0b10111110,  // 6
  0b11100000,  // 7
  0b11111110,  // 8
  0b11110110,  // 9
  0b11101110,  // A
  0b00111110,  // b
  0b00011010,  // C
  0b01111010,  // d
  0b10011110,  // E
  0b10001110,  // F
  0b00000001   // .
};
//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clkPin = 6;
//Pin connected to DS of 74HC595
int dtPin = 7;
void setup() {
  // put your setup code here, to run once:
  // set the serial port at 9600
  Serial.begin(9600);
  delay(1000); 
  // set the 74HC595 Control pin as output
  pinMode(latchPin, OUTPUT);    //ST_CP of 74HC595
  pinMode(clkPin, OUTPUT);      //SH_CP of 74HC595
  pinMode(dtPin, OUTPUT);       //DS of 74HC595
  // initialize I2C Libs 
  Wire.begin();
  // start MAX30205 temperature read in continuous mode, active mode
  tempSensor.begin();   
}
void loop() {
  float temp = tempSensor.getTemperature(); // read temperature for every 5ms
  if( fahrenheittemp == true){
    temp = (temp * 1.8) + 32 ; // convert the temperature from Celcius to Farenhite using formula of [ T(°C) × 1.8 + 32 ]
    Serial.print(temp ,2);
    Serial.println("°f" );
  }else{
    Serial.print(temp ,2);
    Serial.println("°c" );
  }
  // saperate 3 digits from the current temperature (like if temp = 31.23c, )
  int dispDigit1=(int)temp/10;      // digit1 3
  int dispDigit2=(int)temp%10;      // digit2 1
  int dispDigit3=(temp*10)-((int)temp*10);  //digit3 2
/*
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(dispDigit1);
  Serial.print(" ");
  Serial.print(dispDigit2);
  Serial.print(" ");
  Serial.println(dispDigit3);
*/
  // display digits into 3, 7segment display.
  digitalWrite(latchPin, LOW);
  if(commonCathode == true){
    shiftOut(dtPin, clkPin, LSBFIRST, digit_pattern[dispDigit3]);
    shiftOut(dtPin, clkPin, LSBFIRST, digit_pattern[dispDigit2]|digit_pattern[16]);   // 1. (Digit+DP)
    shiftOut(dtPin, clkPin, LSBFIRST, digit_pattern[dispDigit1]);
  }else{
    shiftOut(dtPin, clkPin, LSBFIRST, ~(digit_pattern[dispDigit3]));
    shiftOut(dtPin, clkPin, LSBFIRST, ~(digit_pattern[dispDigit2]|digit_pattern[16]));   // 1. (Digit+DP)
    shiftOut(dtPin, clkPin, LSBFIRST, ~(digit_pattern[dispDigit1]));
  }
  digitalWrite(latchPin, HIGH);
  delay(500);
}