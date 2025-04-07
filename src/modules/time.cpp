#include "time.h"
#include "light.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <limits.h>

unsigned long minute = 0;
unsigned long oldmod = ULONG_MAX;
unsigned long overflow = 0;

// Arduino functions
void time_setup()
{
    server.on("/sync", handleSync);
    server.on("/time", handleTimechange);
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
void time_loop()
{
    // millis is not run / incremented every millissecond -> workaround
    // also some more math to circumvent millis() overflowing every 50 days

    unsigned long currenttime = millis();

    unsigned long modulo = (currenttime - minute) % ms_minute;

    // regular case: modulo turns && no overflow
    if (modulo < oldmod && minute < currenttime ) 
    {
        daytime = (daytime + 1) % min_day;
        minute = currenttime;
        overflow = 0;
    }
    // odd case: overflow of millis
    if (minute > currenttime)
    {
        // calc distance to overflow and add to currenttime
    }

    oldmod = modulo;
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

