/*******
 
 Credit - https://randomnerdtutorials.com/guide-for-mq-2-gas-smoke-sensor-with-arduino/

 More Resource 
 * https://lastminuteengineers.com/mq2-gas-senser-arduino-tutorial/
 * https://circuitdigest.com/microcontroller-projects/interfacing-mq2-gas-sensor-with-arduino
 * https://wiki.dfrobot.com/Analog_Gas_Sensor_SKU_SEN0127
 * https://projecthub.arduino.cc/m_karim02/arduino-and-mq2-gas-sensor-f3ae33
 * https://www.instructables.com/How-to-use-MQ2-Gas-Sensor-Arduino-Tutorial/
 * 

*******/

int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);
}