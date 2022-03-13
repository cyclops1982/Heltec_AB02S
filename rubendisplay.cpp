#include "rubendisplay.h"

void RubenDisplay::WriteOut(char *text)
{
    _display.clear();
    _display.drawString(10, 10, text);
    _display.display();
}