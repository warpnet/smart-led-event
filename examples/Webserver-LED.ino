#define DEBUG

#include "LED.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* SSID = "";
const char* SSID_PASSWORD = "";
const char* WEBPAGE =
"<!DOCTYPE html>"
"<html>"
"<head>"
"    <title>Color pickert</title>"
"    <style>"
"    </style>"
"    <script>"
"	    function change(key, value) {"
"			var xhr = new XMLHttpRequest();"
"			xhr.open(\"POST\", \"/\");"
"			xhr.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");"
"			xhr.send(key + \"=\" + value);"
"		}"
"</script>"
"</head>"
""
"<body>"
"    <div class=\"field\">"
"	 <label>Color:</label>"
"    <input type=\"color\" name=\"color\" value=\"#ffffff\" onchange=\"change(\'color\', this.value);\">"
"	 <label>Warmth:</label>"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"warmth\" onchange=\"change(\'warmth\', this.value);\">"
"	 <label>Brightness:</label>"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"brightness\" onchange=\"change(\'brightness\', this.value);\">"
"	 <label>Pulsate</label>"
"    <input type=\"checkbox\" name=\"pulsate\" onchange=\"change(\'pulsate\', this.checked);\">"
"	 <label>Rainbow</label>"
"    <input type=\"checkbox\" name=\"rainbow\" onchange=\"change(\'rainbow\', this.checked);\">"
"    </div>"
"</body>"
"</html>";

LED led = LED();
ESP8266WebServer webserver(80);

void processRequest() {
	Serial.print("Client: ");
	Serial.println(webserver.client());

	if (webserver.method() == HTTP_POST) {
		#ifdef DEBUG
			Serial.println("Arguments: ");
		#endif
		for (int i = 0; i < webserver.args() - 1; i++) {
			#ifdef DEBUG
				Serial.println(webserver.argName(i) + " = " + webserver.arg(i));
			#endif
			if (webserver.argName(i) == "color") {
				led.set_StaticColor(webserver.arg(i));
			}
			else if (webserver.argName(i) == "warmth") {
				led.set_Warmth(webserver.arg(i).toInt());
			}
			else if (webserver.argName(i) == "brightness") {
				led.set_Brightness(webserver.arg(i).toInt());
			}
			else if (webserver.argName(i) == "pulsate") {
				if (webserver.arg(i) == "true") {
					led.enable_Pulsate();
				}
				else {
					led.disable_Pulsate();
				}
			}
			else if (webserver.argName(i) == "rainbow") {
				if (webserver.arg(i) == "true") {
					led.enable_Rainbow();
				}
				else {
					led.disable_Rainbow();
				}
			}
		}
		webserver.send(200, "text/html");
	}
	// Handle other requests.
	else {
		webserver.send(200, "text/html", WEBPAGE);
	}
}

void setup() {
  Serial.begin(115200);

  // Setup the wifi connection
  Serial.println("Wifi connecting");
  WiFi.begin(SSID, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected: ");
  Serial.println(WiFi.localIP());

  // Setup the webserver
  webserver.on("/", processRequest);
  webserver.begin();
  Serial.println("Webserver started.");
}

void loop() {
  webserver.handleClient();
  led.loop();
}

