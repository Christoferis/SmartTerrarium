#include "light.h"
#include <Arduino.h>

// macros 
#define correspondance(state) (state == true ? HIGH : LOW)

static int state = false;
int prevButton = false;

// Arduino functions
void light_setup()
{
    pinMode(LIGHT_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void light_loop()
{

    // loop does multiple things: check button state, set state of light
    // light
    digitalWrite(LIGHT_PIN, correspondance(state));

    
    // button (no spamming)
    if (digitalRead(BUTTON_PIN) == HIGH && !prevButton)
    {
        toggle_light();
        prevButton = true;

        //minuscule delay to prevent to prevent chattering
        delay(10);
    }
    else if (digitalRead(BUTTON_PIN) == LOW)
    {
        prevButton = false;    
    }

}

// get, set, toggle
void set_light(int s)
{
    state = s;
}

String get_light()
{
    return state == 0 ? "Off" : "On";
}

void toggle_light()
{
    state = !state;
}
