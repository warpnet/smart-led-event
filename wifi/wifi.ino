#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define WHITEPIN D5
#define GREENPIN D6
#define BLUEPIN D7
#define REDPIN D8
#define YELLOWPIN D1

// Replace with your network credentials

const char* ssid = "public"; //Enter your Wifi name
const char* password = "secret"; //Enter your Wifi Password

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = LED_BUILTIN;

void setup(void){
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
  
  //the HTML of the web page
  page = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDBlue\"><button>Blue</button></a>&nbsp;<a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p></body></html>";
  //make the LED pin output and initially turned off
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDBlue", [](){
    server.send(200, "text/html", page);
    setColor(0, 0, 255);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    setColor(255, 255, 255);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    setColor(0, 0, 0);
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop(void){
  server.handleClient();
}

void setColor(byte red, byte green, byte blue) {
  analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);
}
