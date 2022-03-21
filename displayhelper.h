#ifndef DISPLAYHELPER_H
#define DISPLAYHELPER_H

#include <Wire.h>
#include "Arduino.h"
#include "HT_SSD1306Wire.h"

class DisplayHelper
{
private:
public:
    DisplayHelper();
    void WriteOut(char *text);
};

#endif