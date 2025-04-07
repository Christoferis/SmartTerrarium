#include "terrarium.h"

#include <DHTesp.h>

DHTesp sensor;

// Arduino type functions
void terrarium_setup()
{
    sensor.setup(DHT_PIN, DHTesp::DHT11);
}

//TODO: See what this library has to offer more
float getHumidity()
{
    return sensor.getHumidity();
}

float getTemperature()
{
    return sensor.getTemperature();
}
