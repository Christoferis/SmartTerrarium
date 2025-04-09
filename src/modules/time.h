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

// utility functions

// returns String representation of time (ms -> 24 hour format)
String toStringMorning();
String toStringEvening();
String toStringDay();

// toggles this module
void toggle();

// arduino functions
void time_setup(void);
void time_loop(void);

// to be used with light submodule
void morning();
void evening();

// to be used with the webserver module
void handleSync();
void handleTimechange();

