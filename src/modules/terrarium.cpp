#include "terrarium.h"

#include <DHTesp.h>
#include <Arduino.h>

DHTesp sensor;

// Arduino type functions
void terrarium_setup()
{
    sensor.setup(DHT_PIN, DHTesp::DHT11);
}

//TODO: See what this library has to offer more
String get_Humidity()
{
    return String(sensor.getHumidity());
}

String get_Temperature()
{
    return String(sensor.getTemperature());
}
