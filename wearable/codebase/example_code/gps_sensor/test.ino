/*
Credit - https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/

More resource files
https://lastminuteengineers.com/neo6m-gps-arduino-tutorial/
https://circuitdigest.com/microcontroller-projects/connect-arduino-with-neo-6m-gps-module
https://microcontrollerslab.com/neo-6m-gps-module-arduino-tutorial/

*/

#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial ss(4, 3);

void setup(){
  Serial.begin(9600);
  ss.begin(9600);
}

void loop(){
  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
}