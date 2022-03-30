#include "gpshelper.h"

GPSHelper::GPSHelper()
{
    ss.begin(9600);
}

bool GPSHelper::WriteStuff()
{
    Serial.printf("Performing GPS fix.");

    unsigned long start = millis();
    do
    {
        Serial.printf("In do...: %d\n", ss.available());
        while (ss.available())
        {
            gps.encode(ss.read());
        }
    } while (millis() - start < 5000);

    Serial.println("No more SS available and after 5 sec.");

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        Serial.println("No GPS detected: check wiring.");
        return false;
    }

    while (!gps.location.isValid())
    {
        do
        {
            if (ss.available())
            {
                gps.encode(ss.read());
            }
        } while (gps.charsProcessed() < 100);
    }

    Serial.print("LAT: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", LON: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(", ALT: ");
    Serial.print(gps.altitude.meters());
    Serial.println();

    return true;
}
