#include "gpshelper.h"

Air530Class GPS;

GPSHelper::GPSHelper()
{
    GPS.begin();
}

bool GPSHelper::WriteStuff()
{
    Serial.printf("Performing GPS fix.");
    uint32_t starttime = millis();
    while ((millis() - starttime) < 5000)
    {
        Serial.printf("GPS AVailable: %d\n", GPS.available());
        while (GPS.available() > 0)
        {
            GPS.encode(GPS.read());
        }
        delay(10);
    }

    Serial.printf("GPS Location: %d\n", GPS.location.isValid());
    Serial.printf("GPS lat/long: %lf / %lf\n", GPS.location.lat(), GPS.location.lng());

    return true;
}
