/**
 * Credit - https://sensorkit.arduino.cc/sensorkit/module/lessons/lesson/04-the-buzzer
 * 
 * More Resource
 * 
*/


#define BUZZER 5
 
void setup()
{  
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
}
 
void loop()
{
  tone(BUZZER, 85); //Set the voltage to high and makes a noise
  delay(1000);//Waits for 1000 milliseconds
  noTone(BUZZER);//Sets the voltage to low and makes no noise
  delay(1000);//Waits for 1000 milliseconds
}