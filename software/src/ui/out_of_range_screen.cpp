#include "out_of_range_screen.hpp"

OutOfRangeScreen::OutOfRangeScreen(M5Display &lcd, Sensor &sensor)
    : Screen(lcd), sensor(sensor)
{
}

void OutOfRangeScreen::draw()
{
    setColor(WHITE, RED);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
    lcd.print("OUT OF RANGE !!");

    lcd.setTextSize(4);
    lcd.setCursor(0, 40);
    lcd.print("h:         mm");
    lcd.setTextSize(3);
    lcd.setCursor(0, 110);
    lcd.print("Heigt must be within 10 - 115 mm");
}

void OutOfRangeScreen::update()
{
    lcd.setCursor(80, 40);
    lcd.setTextSize(4);
    lcd.printf("%6.2lf", sensor.convertedValue());
}