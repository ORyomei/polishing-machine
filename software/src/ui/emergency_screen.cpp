#include "emergency_screen.hpp"

void EmergencyScreen::draw()
{
    setColor(WHITE, RED);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
    lcd.print("EMERGENCY");
}

void EmergencyScreen::update()
{
}