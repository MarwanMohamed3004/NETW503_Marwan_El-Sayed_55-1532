#include <ESP8266WiFi.h>
#include <ThingsBoard.h>
#include<WiFiClient.h>
#define TB_SERVER "thingsboard.cloud"
#define TOKEN "cCIGsnLcusbIkCY3Ykku"

const char* ssid = "marwan";
const char* password = "30042003mM";
const char* serverIP = "192.168.100.51"; // IP address of your Python server
const int serverPort = 55556;

const int ldrPin = A0;

WiFiClient client;
ThingsBoard tb(client);


void setup() {
  Serial.begin(9600);
  delay(10000);
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
  if (!tb.connected()) {
    // Attempt to connect to the server
    if (tb.connect(TB_SERVER, TOKEN)) {
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection to server failed");
      return;
    }
  }

  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  // Send the LDR value as a string
  tb.sendTelemetryFloat("light",ldrValue);
  tb.loop();


  

 
}