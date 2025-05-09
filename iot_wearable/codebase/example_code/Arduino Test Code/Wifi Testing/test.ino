/*
  Credit - DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

// Include SPI and WiFi Libraries
#include <SPI.h>
#include <WiFiNINA.h>

// WiFi Credentials (edit as required)
char ssid[] = "xxxxxxxxx";      // Wifi SSID
char pass[] = "xxxxxxxxx";       // Wifi password

int status = WL_IDLE_STATUS;

// Initialize the Wifi client
WiFiSSLClient client;

void connectToAP() {
  // Connect to Wifi Access Point
  
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);

    // wait 1 second for connection:
    delay(1000);
    Serial.println("Connected...");
  }
}

void printWifiStatus() {
  // Print results to serial monitor  
 
 // Network SSID  
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // Device IP address
  IPAddress ip = WiFi.localIP(); 
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void setup() {
  
  // Start the Serial port
  Serial.begin(9600);
  
  while (!Serial) {
    ; // Wait for serial port to connect.
  }
  
  // Check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module failed!");
    while (true);
  }
   
  connectToAP();  
    
  printWifiStatus();
  
}

void loop() {
}