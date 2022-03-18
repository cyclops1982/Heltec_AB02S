
#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>
#include "rubendisplay.h"

RubenDisplay *disp;
VL53L0X sensor;

void setup()
{
	Serial.begin(115200);
	Serial.printf("Booting version: 0.1\n");
	Wire.begin();

	pinMode(Vext, OUTPUT);
	digitalWrite(Vext, LOW); // set vext to high

	disp = new RubenDisplay();

	sensor.setTimeout(500);
	while (!sensor.init())
	{

		Serial.println("Failed to detect and initialize sensor!");
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