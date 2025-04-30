#include "time.h"
#include "light.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <limits.h>
#include <stdlib.h>

// attributes
unsigned long oldtime = 0;
unsigned long internal = 0;

// preset times
unsigned long daytime = 0;
unsigned long morningtime;
unsigned long eveningtime;

unsigned long morningtime_offset = 0;
unsigned long eveningtime_offset = 0;

unsigned long offset = 0;
int timeswitch = 0;

// used to disable this feature entirely 
int enabled = 0;

// Arduino functions
void time_setup()
{
    server.on("/sync", handleSync);
}

// TODO: Rewrite
/*
    Things to consider:
    - modulo not deterministic, function may be called in irregular intervals
    - millis() overflows every 50 days
    - daytime should be in minutes, for convenience, and rollover every
    - implement auto light in such a way that it can still be overriden with the button
        -> behaviour if light is on and auto light says on -> light stays on
*/
// https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover
// I really forgot how modular calculations work huh

void time_loop()
{
    // timekeeping
    unsigned long time = millis();

    //assumed that time jump < than a day
    internal = ((time - oldtime) + internal) % ms_day;

    // sync internal time to external time with offset
    daytime = internal + offset;

    oldtime = time;

    //Action timing second
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
    set_light(false);
}

void evening()
{
    set_light(true);
}

void handleSync()
{
    // offset calc: compare internal time and external time -> offset so that internal = external time
    String thing = server.arg("time");
    char* array = (char*) calloc(sizeof(char), thing.length() + 1);

    thing.toCharArray(array, thing.length() + 1);
    offset = strtoul(array, NULL, 0) - internal;

    free(array);
}

// toString and toggle method
void toggle()
{
    enabled = !enabled;
}

String toStringDay()
{
    // daytime already only goes 24h. make use of that
    String out = "";

    // might not convert correctly
    int hours = daytime / ms_hour;
    int minutes = daytime % (ms_minute * 60);

    out.concat(hours);
    out.concat(":");
    out.concat(minutes);

    return out;
}

String toStringMorning()
{
    // daytime already only goes 24h. make use of that
    String out = "";

    // might not convert correctly
    int hours = morningtime / ms_hour;
    int minutes = morningtime % (ms_minute * 60);

    out.concat(hours);
    out.concat(":");
    out.concat(minutes);

    return out;
}

String toStringEvening()
{
    // daytime already only goes 24h. make use of that
    String out = "";

    // might not convert correctly
    int hours = eveningtime / ms_hour;
    int minutes = eveningtime % (ms_minute * 60);

    out.concat(hours);
    out.concat(":");
    out.concat(minutes);

    return out;
}

