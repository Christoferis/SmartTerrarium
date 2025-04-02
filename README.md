# SmartTerrarium - Expanding a Terrarium using Technology!

## What?
A Terrarium in its simplest form houses plants in an isolated environment. This project aims to also include some tech with a Terrarium in order to get useful data and to make a Terrarium nicer, by including lighting.
This is done mostly for fun but also to keep the Terrarium healthy and interesting.
### What is the scope of this project?
The Scope of this project is to enhance an existing Terrarium with Sensors and Lighting and I/O in order to easily monitor the Terrarium.
The addition of light makes it also interesting as a decor piece at night and might also help the plants.

Sensor List:
- Temperature
- Humidity

Stimuli List:
- LED

I/O:
- Webserver accessible over a normal Smartphone, no apps needed
- Accessible at any time, as long as Chip is powered

## Parts List
For this project, the following parts are used:
- [NodeMCU D1 mini](https://www.az-delivery.de/products/d1-mini?_pos=2&_psq=nodemc&_ss=e&_v=1.0) (ESP8266 based microcontroller)
- [Asair DHT11](https://www.az-delivery.de/products/5-x-dht11-temperatursensor?_pos=2&_psq=dht11&_ss=e&_v=1.0) Temperature and Humidity Sensor
- LED Fairy Lights
- BC550 NPN Transistor
### Schematic (based on parts list)

```handdrawn-ink
{
	"versionAtEmbed": "0.3.4",
	"filepath": "Ink/Drawing/2025.4.1 - 22.19pm.drawing",
	"width": 500,
	"aspectRatio": 1
}
```
## Implementation
### Idea
- The microcontroller hosts a small webserver in AP mode to which a user can connect.
- upon connection, the user is shown a webpage delivering desired information about the terrarium
- to make connection easier, a programmed NFC Tag may be used to make connection process automated 
### Frameworks and Technologies
- Arduino
- PlatformIO
### Libraries used

