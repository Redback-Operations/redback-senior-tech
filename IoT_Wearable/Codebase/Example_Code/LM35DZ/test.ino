/**
 * Credit - https://www.instructables.com/ARDUINO-TEMPERATURE-SENSOR-LM35/
 * 
 * More Resource
 * https://www.electronicwings.com/arduino/lm35-interfacing-with-arduino-uno
 * https://www.makerguides.com/lm35-arduino-tutorial/
 * https://lastminuteengineers.com/lm35-temperature-sensor-arduino-tutorial/
 * https://cdreimer.medium.com/lm35-a-not-so-simple-temperature-sensor-for-the-arduino-a62caf0c2cfd
*/

int val;
int tempPin = 1;

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    val = analogRead(tempPin);
    float mv = (val / 1024.0) * 5000;
    float cel = mv / 10;
    float farh = (cel * 9) / 5 + 32;

    Serial.print("TEMPRATURE = ");
    Serial.print(cel);
    Serial.print("*C");
    Serial.println();
    delay(1000);

    /* uncomment this to get temperature in farenhite
    Serial.print("TEMPRATURE = ");
    Serial.print(farh);
    Serial.print("*F");
    Serial.println();


    */
}