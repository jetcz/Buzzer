#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//low is active
int led = 2;
int relay = 0;

ESP8266WebServer server(80);

String www =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<link rel=\"icon\" href=\"data:, \">"
"<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">"
"<title>Zvonek</title>"
"<style>"

".button{"
"background-color: Green;"
"border: none;"
"color: white;"
"padding: 25px 50px;"
"text-align: center;"
"text-decoration: none;"
"cursor: pointer;"
"font-size: 10em;"
"box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);"
"-webkit-transition-duration: 0.4s;"
"}"

".button:focus{"
"opacity: 0.5;"
"cursor: not-allowed;"
"box-shadow: none;"
"}"

".wrapper{"
"width: 100%;"
"height: 1000px;"
"display: flex;"
"align-items: center;"
"justify-content: center;"
"}"

"</style>"
"</head>"

"<body>"
"<form action=\"/\" method=\"post\">"
"<div class=\"wrapper\">"
"<button type=\"submit\" class=\"button\">Zabzuc</button>"
"</div>"
"</form>"
"</body>"
"</html>";

void setup()
{
	//Serial.begin(115200);
	digitalWrite(relay, HIGH);
	digitalWrite(led, HIGH);

	pinMode(led, OUTPUT);
	pinMode(relay, OUTPUT);

	WiFi.begin("ssid", "password");

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		//Serial.print(".");
	}

	//WiFi.printDiag(Serial);

	server.on("/", HTTP_GET, handleRoot);
	server.on("/", HTTP_POST, handleButton);

	server.begin();
}

void handleRoot()
{
	server.send(200, "text/html", www);
}

void handleButton()
{
	ActivateRelay(3);
	server.send(200, "text/html", www);
}

void loop()
{
	server.handleClient();
}

void ActivateRelay(int sec)
{
	digitalWrite(relay, LOW);
	digitalWrite(led, LOW);
	delay(sec * 1000);
	digitalWrite(relay, HIGH);
	digitalWrite(led, HIGH);
}