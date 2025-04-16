#pragma once
#include "main.h"

/*
    This module a LED Fairy Light strip on or off.
    It can either be turned on or off via the time module or
    via a button that this module keeps track off
*/

#define LIGHT_PIN D2
#define BUTTON_PIN D1


// functions
void light_setup(void);
void light_loop(void);

void toggle_light();
void set_light(int);
String get_light();