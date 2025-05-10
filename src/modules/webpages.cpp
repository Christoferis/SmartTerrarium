#include "webpages.h"

// builtin
#include <Arduino.h>
#include <FS.h>

// internal
#include "main.h"
#include "terrarium.h"
#include "light.h"
#include "time.h"
#include "util/html.h"

// declarations
htmlTemplate root;
htmlTemplate settings;

// extra pages
void webpages_error();


void webpages_setup()
{
    // prepare error page (just in case)

    if (!SPIFFS.begin())
    {
        server.on("/", webpages_error);
        return;
    }

    File r = SPIFFS.open("/index/index.html", "r");
    File s = SPIFFS.open("/timeset/settings.html", "r");

    root = htmlTemplate(r.readString());
    settings = htmlTemplate(s.readString());

    r.close();
    s.close();

    // rule adding: root
    root.addRule((htmlRule){.identifier = "temp" , .function = get_Temperature});
    root.addRule((htmlRule){.identifier = "humid", .function = get_Humidity});
    root.addRule((htmlRule){.identifier = "light", .function = get_light});
    root.addRule((htmlRule){.identifier = "terrariumtime", .function = toStringDay});

    // rule adding: settings


    // server registering
    server.on("/", webpages_root);
    server.on("/time", webpages_settings);
}

void webpages_root()
{
    server.send(200, "text/html", root.serve());
}

void webpages_settings()
{
    server.send(200, "text/html", settings.serve());
}

void webpages_error()
{
    server.send(200, "text/plain", "SPIFFS ERROR");
}