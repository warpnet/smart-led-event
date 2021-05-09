#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define GREEN  D6
#define BLUE   D7
#define RED    D8
#define YELLOW D1
#define WHITE  D5

const char* SSID = "";
const char* SSID_PASSWORD = "";
const char* WEBPAGE =
"<!DOCTYPE html>"
"<html>"
"<head>"
"    <title>Color pickert</title>"
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
"    <input type=\"color\" name=\"color\" value=\"#ffffff\" onchange=\"change(\'color\', this.value);\">"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"yellow\" onchange=\"change(\'yellow\', this.value);\">"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"white\" onchange=\"change(\'white\', this.value);\">"
"    <input type=\"checkbox\" name=\"pulse\" onchange=\"change(\'pulse\', this.checked);\">"
"</body>"
"</html>";


char yellow = 125;
char white = 0;

bool yellowDirection = false;
bool whiteDirection = false;

short ticker = 0;

bool pulse = false;

ESP8266WebServer webserver(80);

void processRequest() {
	Serial.print("Client: ");
	Serial.println(webserver.client());

	if (webserver.method() == HTTP_POST) {
		Serial.println("Arguments: ");
		for (int i = 0; i < webserver.args() - 1; i++) {
			Serial.println(webserver.argName(i) + " = " + webserver.arg(i));
			if (webserver.argName(i) == "color") {
				setColor(webserver.arg(i));
			}
			else if (webserver.argName(i) == "white") {
				setWhite(webserver.arg(i));
			}
			else if (webserver.argName(i) == "yellow") {
				setYellow(webserver.arg(i));
			}
			else if (webserver.argName(i) == "pulse") {
				setPulse(webserver.arg(i));
			}
		}
		webserver.send(200, "text/html");
	}
	// Handle other requests.
	else {
		webserver.send(200, "text/html", WEBPAGE);
	}
}

bool setColor(String color) {
	if (color.length() == 7) {

		// Get rid of '#' and convert it to integer
		int number = (int) strtol( &color[1], NULL, 16);

		// Split them up into r, g, b values
		int r = number >> 16;
		int g = number >> 8 & 0xFF;
		int b = number & 0xFF;

		String msg = "R:" + String(r) + " G:" + String(g) + " B:" + String(b);
		Serial.println(msg);

		analogWrite(RED, r);
		analogWrite(GREEN, g);
		analogWrite(BLUE, b);

		return true;
	}

	return false;
}

void setWhite(String value) {
	if(value.toInt() >= 0 <=255) {
		analogWrite(WHITE, value.toInt());
	}
}

void setYellow(String value) {
	if(value.toInt() >= 0 <=255) {
		analogWrite(YELLOW, value.toInt());
	}
}

void setPulse(String value) {
	if (value == "false") {
		pulse = false;
	}
	else {
		pulse = true;
	}
}

void eventticker(){
	ticker++;
	//Pulse
	if (pulse) {
		if (ticker > 500) {
			if (yellow >= 255 || yellow <= 0) {
				yellowDirection = !yellowDirection;
			}
			if (white >= 255 || white <= 0) {
				whiteDirection = !whiteDirection;
			}
			if (yellowDirection) {
				yellow++;
			}
			else {
				yellow--;
			}
			if (whiteDirection) {
				white++;
			}
			else {
				white--;
			}
			analogWrite(YELLOW, yellow);
			analogWrite(WHITE, white);

			ticker = 0;
		}
	}
}

void setup(void){
	// Initialize PIN's
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(WHITE, OUTPUT);
	pinMode(YELLOW, OUTPUT);

	// Setup the serial console.
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

void loop(void){
	webserver.handleClient();
	eventticker();
}
