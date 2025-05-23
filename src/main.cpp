#include "main.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiAP.h>
#include <string.h>
#include "util/html.h"
#include <FS.h>


// modules
#include "modules/light.h"
#include "modules/terrarium.h"
#include "modules/time.h"

IPAddress ip(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WiFiAPClass wifi;

ESP8266WebServer server(80);

htmlTemplate test;
String page;

// prototypes
void handleRoot();
void handleTest();
void g();

// Testing Webserver
void setup()
{
  
  SPIFFS.begin();

  File f = SPIFFS.open("/test.html", "r");
  page = f.readString();

  wifi.softAPConfig(ip, ip, subnet);
  wifi.softAP("SmartTerrarium", NULL);

  test = htmlTemplate(page);

  server.on("/", g);

  //setup modules
  // terrarium_setup();
  // light_setup();
  time_setup();


  Serial.begin(115200);
  server.begin();
}

void loop()
{
  server.handleClient();

  time_loop();

  // Serial.println(page);
  // Serial.println("---");
  Serial.println(toStringDay());

  delay(500);
}

void g()
{
  server.send(200, "text/html", page);
}
