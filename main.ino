
#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>
#include "displayhelper.h"

#define VERSION "0.2"

DisplayHelper *disp;
VL53L0X sensor;

void setup()
{
	Serial.begin(115200);
	Serial.printf("Booting version: %s\n", VERSION);

	disp = new DisplayHelper();
	disp->WriteOut("Loading...");

	// Enable vExt output voltage
	pinMode(Vext, OUTPUT);
	digitalWrite(Vext, LOW);
	delay(10);

	// Begin i2c
	Wire.begin();

	sensor.setTimeout(500);
	while (!sensor.init())
	{

		Serial.println("Failed to detect and initialize sensor!");
		disp->WriteOut("Error");
		delay(1000);
	}
}

void loop()
{
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");
	if (sensor.timeoutOccurred())
	{
		Serial.print(" TIMEOUT");
	}

	char text[30];
	snprintf(text, 30, "Distance: %dmm", sensor.readRangeSingleMillimeters());
	Serial.println(text);
	disp->WriteOut(text);
	delay(1000);
}