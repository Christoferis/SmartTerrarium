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
String g();

// Testing Webserver
void setup()
{
  
  SPIFFS.begin();

  File f = SPIFFS.open("/test.html", "r");
  page = f.readString();

  test = htmlTemplate(page);

  test.addRule((htmlRule){.identifier = "bibinos", .function = g});


  //setup modules
  // terrarium_setup();
  // light_setup();
  time_setup();


  Serial.begin(115200);
  server.begin();
}

void loop()
{

  Serial.println(page);
  Serial.println("---");
  Serial.println(test.serve());

  delay(2000);
}

String g()
{
  return "Hello World";
}
