#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "your_ssid";
const char* password = "supersecretpassword";

#define WHITEPIN D5
#define GREENPIN D6
#define BLUEPIN D7
#define REDPIN D8
#define YELLOWPIN D1

void turnAllLedOff() {
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(WHITEPIN, 0);
  analogWrite(YELLOWPIN, 0);
}

void setup() {
  // Setup the serial console
  Serial.begin(115200);
  delay(1000);
  Serial.println('\n');

  // Connect to the network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  // Wait for the Wi-Fi to connect
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  // Send the IP address of the ESP8266 to the computer
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Setup the LED pins
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);

  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(WHITEPIN, 0);
  analogWrite(YELLOWPIN, 0);
}

void loop() {
  // Signal strength.
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

  // Turn green if the signal is strong
  // Adjust these values to suit your needs.
  if (rssi <= -35 && rssi >= -45) {
    turnAllLedOff();
    analogWrite(GREENPIN, 255);
  }

  // Turn orange if the signal is moderate
  // Adjust these values to suit your needs.
  else if (rssi < -45 && rssi >= -50) {
    turnAllLedOff();
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 128);
  }

  // Turn red if the signal is weak
  else {
    turnAllLedOff();
    analogWrite(REDPIN, 255);
  }

  delay(1000);

}
