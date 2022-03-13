#ifndef RUBENDISPLAY_H
#define RUBENDISPLAY_H

#include <Wire.h>
#include "Arduino.h"
#include "HT_SSD1306Wire.h"

class RubenDisplay
{
private:
public:
    RubenDisplay();
    void WriteOut(char *text);
};

#endif