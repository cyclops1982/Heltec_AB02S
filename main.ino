
//#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "rubendisplay.h"

int count;
RubenDisplay disp;

void setup()
{
	Serial.begin(115200);
	Serial.printf("Booting version: 0.1\n");
	count = 0;
}

void loop()
{
	Serial.printf("Count: %d\n", count);

	count++;
	char text[11];
	snprintf(text, 11, "TEST %d", count);
	Serial.println(text);
	//	disp.WriteOut(text);
	delay(100);
}

void WriteDisplay(char *text)
{
}