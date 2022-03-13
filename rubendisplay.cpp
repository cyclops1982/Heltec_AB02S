#include "rubendisplay.h"

SSD1306Wire display(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

RubenDisplay::RubenDisplay()
{
    display.init();
}

void RubenDisplay::WriteOut(char *text)
{
    display.clear();
    display.drawString(10, 10, text);
    display.display();
}