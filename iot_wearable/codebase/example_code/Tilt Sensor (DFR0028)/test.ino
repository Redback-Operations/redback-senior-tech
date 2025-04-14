/**
 * Credit - https://wiki.dfrobot.com/DFRobot_Tilt_Sensor__SKU_DFR0028_
*/

int ledPin = 13;                // Connect LED to pin 13
int switcher = 3;                 // Connect Tilt sensor to Pin3

void setup()
{
  pinMode(ledPin, OUTPUT);      // Set digital pin 13 to output mode
  pinMode(switcher, INPUT);       // Set digital pin 3 to input mode
}
void loop()
{

   if(digitalRead(switcher)==HIGH) //Read sensor value
     {
        digitalWrite(ledPin, HIGH);   // Turn on LED when the sensor is tilted
     }
   else
     {
        digitalWrite(ledPin, LOW);    // Turn off LED when the sensor is not triggered
     }
}

