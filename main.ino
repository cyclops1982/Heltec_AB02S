
#include <Arduino.h>
#include "LoraWAN/LoRaWan_APP.h"
#include "LoraWAN/LoRaWan_Config.h"

#define VERSION "0.2"

static TimerEvent_t wakeUp;
bool lowpower = false;

void onWakeUp()
{
	Serial.printf("Woke up!\n");
	lowpower = false;
}

void setup()
{
	Serial.begin(115200);
	Serial.printf("Booting version: %s\n", VERSION);

	LoRaWAN.ifskipjoin();

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
		switch (deviceState)
		{
		case DEVICE_STATE_INIT:
		{

			LoRaWAN.generateDeveuiByChipID();

			LoRaWAN.init(loraWanClass, loraWanRegion);
			deviceState = DEVICE_STATE_JOIN;
		}

		case DEVICE_STATE_JOIN:
		{
			LoRaWAN.join();
			break;
		}
		case DEVICE_STATE_SEND:
		{
			uint16_t batVol1 = getBatteryVoltageFloat();
			Serial.printf("Send over %d\n", batVol1);
			SetAppData(batVol1);
			delay(100);
			LoRaWAN.send();

			deviceState = DEVICE_STATE_CYCLE;
			break;
		}
		case DEVICE_STATE_CYCLE:
		{
			// Schedule next packet transmission
			txDutyCycleTime = appTxDutyCycle + randr(0, APP_TX_DUTYCYCLE_RND);
			LoRaWAN.cycle(txDutyCycleTime);
			deviceState = DEVICE_STATE_SLEEP;
			break;
		}
		case DEVICE_STATE_SLEEP:
		{
			LoRaWAN.sleep();
			lowpower = true;
			TimerSetValue(&wakeUp, 10000); // trigger after 10s
			TimerStart(&wakeUp);

			break;
		}
		default:
		{
			deviceState = DEVICE_STATE_INIT;
			break;
		}
		}
	}
}

static void SetAppData(uint16_t data)
{
	appDataSize = 4;
	appData[0] = 0x00;
	appData[1] = 0x01;
	appData[2] = data >> 8;
	appData[3] = data;
}

static uint16_t getBatteryVoltageFloat(void)
{
	float temp = 0;
	pinMode(VBAT_ADC_CTL, OUTPUT);
	digitalWrite(VBAT_ADC_CTL, LOW);

	delay(50);

	for (int i = 0; i < 50; i++)
	{ // read 50 times and get average
		temp += analogReadmV(ADC);
	}
	pinMode(VBAT_ADC_CTL, INPUT);
	return (uint16_t)((temp / 50) * 2);
}