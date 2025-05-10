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
unsigned long morningtime = 0;
unsigned long eveningtime = 0;

unsigned long morningtime_offset = 0;
unsigned long eveningtime_offset = 0;

unsigned long offset = 0;
int timeswitch = 0;

// used to disable this feature entirely 
int enabled = 0;

// Arduino functions
void time_setup()
{
    server.on("/timeset", handleSync);
}

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

    //handle sync and optional evening and morning part

    // offset calc: compare internal time and external time -> offset so that internal = external time
    String sync = server.arg("sync");
    char* array = (char*) calloc(sizeof(char), sync.length() + 1);

    sync.toCharArray(array, sync.length() + 1);
    offset = strtoul(array, NULL, 0) - internal;

    free(array);
    
    // if evening and morning arguments are available, read them and stuff
    String morning = server.arg("morning");
    if (!morning.isEmpty()) 
    {
        char* array = (char*) calloc(sizeof(char), morning.length() + 1);

        morning.toCharArray(array, morning.length() + 1);
        offset = strtoul(array, NULL, 0) - internal;

        free(array);
    }

    String evening = server.arg("evening");
    if (!evening.isEmpty()) 
    {
        char* array = (char*) calloc(sizeof(char), evening.length() + 1);

        evening.toCharArray(array, evening.length() + 1);
        offset = strtoul(array, NULL, 0) - internal;

        free(array);
    }
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

