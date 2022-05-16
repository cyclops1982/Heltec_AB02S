#include "displayhelper.h"

SSD1306Wire display2(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

DisplayHelper::DisplayHelper()
{
    display2.init();
}

void DisplayHelper::WriteOut(char *text)
{
    display2.clear();
    display2.drawString(10, 10, text);
    display2.display();
}

DisplayHelper::~DisplayHelper()
{
    display2.clear();
    display2.stop();
}