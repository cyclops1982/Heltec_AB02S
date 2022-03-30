
#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>
#include "displayhelper.h"
#include "gpshelper.h"

#define VERSION "0.2"

static TimerEvent_t wakeUp;
bool lowpower = false;
DisplayHelper *disp;
VL53L0X sensor;

void onWakeUp()
{
	Serial.printf("Woke up!\r\n");
	lowpower = false;
}

void setup()
{
	Serial.begin(115200);
	Serial.printf("Booting version: %s\n", VERSION);

	TimerInit(&wakeUp, onWakeUp);
}

void loop()
{
	if (lowpower)
	{
		lowPowerHandler();
	}
	else
	{
		byte error, address;
		int nDevices;

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
			disp->WriteOut("Sensor error");
			delay(1000);
		}

		Serial.println("Scanning...");
		if (sensor.timeoutOccurred())
		{
			Serial.print("TIMEOUT");
		}

		char text[30];
		snprintf(text, 30, "Distance: %dmm", sensor.readRangeSingleMillimeters());
		Serial.println(text);
		disp->WriteOut(text);
		delay(1000);

		GPSHelper *gpsh = new GPSHelper();
		gpsh->WriteStuff();

		delete gpsh;

		Wire.end();

		digitalWrite(Vext, HIGH);
		delete disp;

		lowpower = true;
		TimerSetValue(&wakeUp, 10000); // trigger after 10s
		TimerStart(&wakeUp);
	}
}