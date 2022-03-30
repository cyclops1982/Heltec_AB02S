#ifndef GPSHELPER_H
#define GPSHELPER_H

#include <Arduino.h>
#include <softSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
softSerial ss(GPIO5 /*TX pin*/, GPIO3 /*RX pin*/);

class GPSHelper
{
public:
    GPSHelper();
    bool WriteStuff();
};

#endif