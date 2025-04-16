#pragma once
#include "main.h"

/*
    Interact with the DHT Family of Temperature and Humidity Sensors
    This Module acts as an implementation and wrapper around the DHTesp lib
*/

// defines
#define DHT_PIN D3

// Arduino Functions
void terrarium_setup();

// wrappers
String get_Humidity();
String get_Temperature();