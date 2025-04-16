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
    if (daytime <= morningtime + ms_seconds && daytime >= morningtime - ms_seconds && enabled)
    {
        morning();
        
    } else if (daytime <= eveningtime + ms_seconds && daytime >= eveningtime - ms_seconds && enabled)
    {
        evening();
    }
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
    

}