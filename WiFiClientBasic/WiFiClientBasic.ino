#include <ESP8266WiFi.h>

const char* ssid = "iPhone2";
const char* password = "marwan333";
const char* serverIP = "172.20.10.3"; // IP address of your Python server
const int serverPort = 55657;

const int ldrPin = A0;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check if connected to the server
  if (!client.connected()) {
    // Attempt to connect to the server
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection to server failed");
      return;
    }
  }

  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  // Send the LDR value as a string
  client.println(String(ldrValue));

  // Wait for acknowledgment
  while (client.available() == 0) {
    delay(100);
  }

  // Read and print the acknowledgment
  String ack = client.readStringUntil('\r');
  Serial.println("Server acknowledgment: " + ack);

  delay(500);
}