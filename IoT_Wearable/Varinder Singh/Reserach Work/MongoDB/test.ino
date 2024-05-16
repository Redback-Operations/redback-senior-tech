// Include the necessary libraries
#include <WiFiNINA.h>
#include <WiFiSSLClient.h>

// Your WiFi network credentials
char ssid[] = "YourWiFiSSID"; // Replace with your network SSID
char pass[] = "YourWiFiPassword"; // Replace with your network password

// MongoDB Atlas Data API endpoint
char server[] = "ap-southeast-2.aws.data.mongodb-api.com";
int port = 443; // HTTPS port

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);

  // Connect to WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Create an HTTPS client instance
  WiFiSSLClient client;
  if (!client.connect(server, port)) {
    Serial.println("Connection failed!");
    return;
  }

  // Generate a random number between 0 and 100
  int randomNumber = random(0, 101);

  // HTTP request headers and body
  String headers =
    "POST /app/data-bhiqc/endpoint/data/v1/action/insertOne HTTP/1.1\r\n"
    "Host: ap-southeast-2.aws.data.mongodb-api.com\r\n"
    "Content-Type: application/json\r\n"
    "api-key: APIKEY\r\n" // Replace with your API key
    "Content-Length: ";

  String requestBody =
    "{"
    "\"collection\":\"sensordata\","
    "\"database\":\"database\","
    "\"dataSource\":\"sit314\","
    "\"document\":{\"value\": " + String(randomNumber) + "}" // Send the random number as the data
    "}";

  // Send the HTTP request
  client.print(headers);
  client.print(requestBody.length());
  client.print("\r\n\r\n");
  client.print(requestBody);

  // Read and print the response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }

  // Close the connection
  client.stop();
}

void loop() {
  // You can add other code here if needed
}