#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiAP.h>

IPAddress ip(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WiFiAPClass wifi;

ESP8266WebServer server(80);

String webpage =
"<!DOCTYPE html><html><head><title>Simple Test Site</title><script>function sendData() {var xhr = new XMLHttpRequest();xhr.open('POST', 'http://192.168.4.1/test', true);xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');xhr.onload = function() {if (xhr.status >= 200 && xhr.status < 400) {console.log('Data sent successfully!');} else {console.error('Request failed!');}};xhr.onerror = function() {console.error('Connection error!');};xhr.send('value=1');}</script></head><body><button onclick='sendData()'>Send</button></body></html>";

// prototypes
void handleRoot();
void handleTest();

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
  server.on("/test", handleTest);
  
  digitalWrite(LED_BUILTIN, HIGH);
  server.begin();
}

void handleRoot()
{
  server.send(200, "text/html", webpage);
  // Serial.println(server.arg("value"));
}

void handleTest()
{
  Serial.println(server.arg("value"));
  server.send(200);
}

void loop()
{
  server.handleClient();
}
