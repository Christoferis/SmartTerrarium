#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiAP.h>

IPAddress ip(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WiFiAPClass wifi;

ESP8266WebServer server(80);

String webpage = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Hello, World!</title>"
"</head>"
"<body>"
"<h1>Hello, World!</h1>"
"</body>"
"</html>";

// prototypes
void handleRoot();

// Testing Webserver
void setup()
{
  Serial.begin(115200);

  Serial.println("Starting Server...");
  // setup Webserver
  // TODO: add captive portal

  wifi.softAPConfig(ip, ip, subnet);
  wifi.softAP("SmartTerrarium", NULL);

  // register root
  server.on("/", handleRoot);
  
  digitalWrite(LED_BUILTIN, HIGH);
  server.begin();
}

void handleRoot()
{
  server.send(200, "text/html", webpage);
  Serial.println(server.args());
}

void loop()
{
  server.handleClient();
}
