#ifndef DISPLAYHELPER_H
#define DISPLAYHELPER_H

#include <Wire.h>
#include <Arduino.h>
#include <HT_SSD1306Wire.h>

SSD1306Wire display(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

class DisplayHelper
{
private:
public:
    DisplayHelper();
    ~DisplayHelper();
    void WriteOut(char *text);
};

#endif