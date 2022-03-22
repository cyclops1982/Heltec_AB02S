#include "displayhelper.h"

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