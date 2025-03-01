#include "screen.hpp"

void Screen::setColor(uint16_t fgColor, uint16_t bgColor)
{
    lcd.fillScreen(bgColor);
    lcd.setTextColor(fgColor, bgColor);
}