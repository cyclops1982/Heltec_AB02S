#include "displayhelper.h"

SSD1306Wire display(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

DisplayHelper::DisplayHelper()
{
    display.init();
}

void DisplayHelper::WriteOut(char *text)
{
    display.clear();
    display.drawString(10, 10, text);
    display.display();
}

DisplayHelper::~DisplayHelper()
{
    display.clear();
    display.stop();
}