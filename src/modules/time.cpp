#include "time.h"
#include "light.h"
#include "util/minimath.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <limits.h>
#include <stdlib.h>

// attributes
unsigned long oldtime = 0;

// preset times
unsigned long daytime = 0;
unsigned long morningtime = 0x35c9880;
unsigned long eveningtime = 0x35804a0;

unsigned long morningtime_offset = 0;
unsigned long eveningtime_offset = 0;

// used to disable this feature entirely 
int enabled = 0;

// prototype
String toStringTime(long ms);

// Arduino functions
void time_setup()
{
    server.on("/timeset", handleSync);
    Serial.println("Finished Time Module Setup");
}

void time_loop()
{
    // new version
    unsigned long time = millis();
    daytime = ((time - oldtime) + daytime) % ms_day;
    oldtime = time;

    //Action timing second
    // idea: center the flip not on midnight but on the time of activation itself
    // aka 0 is at the time when morning activates -> from this point there exists a pre and after time
    // also obeyed by underflow
    // remember: works because of unsigned integers

    if (morningtime_offset > daytime - morningtime)
    {
        morning();
    }

    if (eveningtime_offset > daytime - eveningtime)
    {
        evening();
    }

    morningtime_offset = daytime - morningtime;
    eveningtime_offset = daytime - eveningtime;
}

// time sensitive functions
void morning()
{
    Serial.println("morning");
    set_light(false);
}

void evening()
{
    // Serial.println("evening");
    // set_light(true);
}

void handleSync()
{
    //handle sync and optional evening and morning part
    // new thing: just set to sync time (no arithmatic since this here is the equivalent of a quartz clock)

    String sync = server.arg("sync");
    daytime = stringtoul(sync);

    // if evening and morning arguments are available, read them and stuff
    String morning = server.arg("morning");
    if (!morning.isEmpty()) 
    {
        morningtime = stringtoul(morning);
    }

    String evening = server.arg("evening");
    if (!evening.isEmpty()) 
    {
        eveningtime = stringtoul(evening);
    }

    server.send(200);
}

// toString and toggle method
void toggle()
{
    enabled = !enabled;
}

String toStringTime(long ms)
{
    // daytime already only goes 24h. make use of that
    String out = "";

    // might not convert correctly
    int hours = ms / ms_hour;
    int minutes = (ms % ms_hour) / ms_minute;

    out.concat(hours);
    out.concat(":");

    if (minutes < 10) {
        out.concat("0");        
    }

    out.concat(minutes);

    return out;
}

String toStringDay()
{
    return toStringTime(daytime);
}


String toStringEvening()
{
    return toStringTime(eveningtime);
}

String toStringMorning()
{
    return toStringTime(morningtime);
}

