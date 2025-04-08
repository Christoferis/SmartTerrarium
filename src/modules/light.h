#pragma once
#include "main.h"

/*
    This module a LED Fairy Light strip on or off.
    It can either be turned on or off via the time module or
    via a button that this module keeps track off
*/

#define LIGHT_PIN 2
#define BUTTON_PIN 3


// functions
void light_setup(void);
void light_loop(void);

void toggle_light();
void set_light(int);
int get_light();

