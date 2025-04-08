#pragma once
#include "main.h"

/*
    Track time for time sensitive functions
*/

extern ESP8266WebServer server;

// various values as millis or minutes
#define ms_day 0x5265c00L
#define ms_seconds 0x3e8L

#define min_day 0x5a0

// attributes

//start with overflow

//daytime in ms
unsigned long daytime = 0;
unsigned long morningtime;
unsigned long eveningtime;

// synchronization with phone time
unsigned long offset = 0;


int timeswitch = 0;

// converts current time keeping to a real time of day in minutes
String toString();

// arduino functions
void time_setup(void);
void time_loop(void);

// to be used with light submodule
void morning();
void evening();

// to be used with the webserver module
void handleSync();
void handleTimechange();

