#include "off_screen.hpp"

OffScreen::OffScreen(M5Display &lcd, MotorController &motorController, Sensor &sensor)
    : Screen(lcd), motorController(motorController), sensor(sensor)
{
}

void OffScreen::draw()
{
    setColor(WHITE, BLACK);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
    lcd.print("OFF");

    lcd.setTextSize(4);
    lcd.setCursor(0, 40);
    lcd.print("h:         mm");
    lcd.setTextSize(3);
    lcd.setCursor(0, 110);
    lcd.print("UPPER:         mm");
    lcd.setCursor(0, 140);
    lcd.print("LOWER:         mm");

    lcd.setTextSize(2);
    lcd.setCursor(30, 220);
    lcd.print("CONFIG");
}

void OffScreen::update()
{
    lcd.setCursor(80, 40);
    lcd.setTextSize(4);
    lcd.printf("%6.2lf", sensor.convertedValue());
    lcd.setTextSize(3);
    lcd.setCursor(120, 110);
    lcd.printf("%6.2lf", motorController.getUpperPosition());
    lcd.setCursor(120, 140);
    lcd.printf("%6.2lf", motorController.getLowerPosition());
}