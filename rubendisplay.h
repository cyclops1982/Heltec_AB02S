#ifndef rubendisplay_h
#define rubendisplay_h

#include <Wire.h>
#include "HT_SSD1306Wire.h"

class RubenDisplay
{
private:
    SSD1306Wire _display;

public:
    RubenDisplay() : _display(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10)
    {
        _display.init();
    }
    void WriteOut(char *text);
};

#endif