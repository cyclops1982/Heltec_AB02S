#ifndef GPSHELPER_H
#define GPSHELPER_H

#include <Arduino.h>
#include <GPS_Air530.h>

class GPSHelper
{
public:
    GPSHelper();
    bool WriteStuff();
};

#endif