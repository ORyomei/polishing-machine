#include "running_screen.hpp"

RunningScreen::RunningScreen(M5Display &lcd, MotorStateController &motorStateController, MotorController &motorController, Sensor &sensor)
    : Screen(lcd), motorStateController(motorStateController), motorController(motorController), sensor(sensor)
{
}

void RunningScreen::draw()
{
    setColor(BLACK, GREEN);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
    lcd.print("RUNNING");

    lcd.setTextSize(4);
    lcd.setCursor(0, 40);
    lcd.print("h:         mm");
    lcd.setTextSize(3);
    lcd.setCursor(0, 110);
    lcd.print("UPPER:         mm");
    lcd.setCursor(0, 140);
    lcd.print("LOWER:         mm");
}

void RunningScreen::update()
{
    lcd.setCursor(80, 40);
    lcd.setTextSize(4);
    lcd.printf("%6.2lf", sensor.convertedValue());
    lcd.setTextSize(3);
    lcd.setCursor(120, 110);
    lcd.printf("%6.2lf", motorController.getUpperPosition());
    lcd.setCursor(120, 140);
    lcd.printf("%6.2lf", motorController.getLowerPosition());

    lcd.setCursor(0, 190);
    lcd.setTextSize(4);
    if (motorStateController.movingToStandby())
    {
        lcd.print("GoTo STANDBY");
    }
    else
    {
        lcd.print("Reciprocal");
    }
}