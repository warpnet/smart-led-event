// This example is based off of
// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
// and requires extra Libraries (see 2. Install Libraries)

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <SPIFFS.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <Hash.h>
  #include <FS.h>
#endif
#include <ESPAsyncWebServer.h>

// Define pins
#define REDPIN D8
#define BLUEPIN D7
#define GREENPIN D6
#define WHITEPIN D5
#define YELLOWPIN D1
 
// Replace with your network credentials

const char* ssid = ""; //Enter your Wifi name
const char* password = ""; //Enter your Wifi Password
 
AsyncWebServer server(80);   //instantiate server at port 80 (http port)

//the HTML of the web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">
        <title>Colourful webserver</title>
    </head>

    <body>
        <h1>Colourful webserver</h1>
        <p>
            <form action="/led" method="get">
            Red: <input type="range" min="0" max="255" value="0" class="slider" id="inputred" name="inputred"> </br>
            Blue <input type="range" min="0" max="255" value="0" class="slider" id="inputblue" name="inputblue">  </br>
            Green: <input type="range" min="0" max="255" value="0" class="slider" id="inputgreen" name="inputgreen">  </br>
            White: <input type="range" min="0" max="255" value="0" class="slider" id="inputwhite" name="inputwhite">  </br>
            Yellow: <input type="range" min="0" max="255" value="0" class="slider" id="inputyellow" name="inputyellow">  </br>
            <input type="submit" Value="submit">
            </form>
        </p>
    </body>
</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not Found");
}

void setup(void){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);

  // Turn off the colours initially
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(WHITEPIN, 0);
  analogWrite(YELLOWPIN, 0);
  
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/led", HTTP_GET, [] (AsyncWebServerRequest *request) {
    int inputValue ;

    // Get inputred on <ESP_IP>/led?inputred=value
    if (request->hasParam("inputred")) {
      inputValue = request->getParam("inputred")->value().toInt();
      analogWrite(REDPIN, inputValue);
    }

    // Get inputred on <ESP_IP>/led?inputblue=value
    if (request->hasParam("inputblue")) {
      inputValue = request->getParam("inputblue")->value().toInt();
      analogWrite(BLUEPIN, inputValue);
    }

    // Get inputred on <ESP_IP>/led?inputgreen=value
    if (request->hasParam("inputgreen")) {
      inputValue = request->getParam("inputgreen")->value().toInt();
      analogWrite(GREENPIN, inputValue);
    }

    // Get inputred on <ESP_IP>/led?inputwhite=value
    if (request->hasParam("inputwhite")) {
      inputValue = request->getParam("inputwhite")->value().toInt();
      analogWrite(WHITEPIN, inputValue);
    }

    // Get inputred on <ESP_IP>/led?inputyellow=value
    if (request->hasParam("inputyellow")) {
      inputValue = request->getParam("inputyellow")->value().toInt();
      analogWrite(YELLOWPIN, inputValue);
    }

    // Send back to /
    request->redirect("/");
    
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
}
