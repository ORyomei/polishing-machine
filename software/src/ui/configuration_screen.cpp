#include "configuration_screen.hpp"

ConfigurationScreen::ConfigurationScreen(M5Display &lcd, MotorController &motorController, Configurator &configurator, Sensor &sensor)
    : Screen(lcd), motorController(motorController), configurator(configurator), sensor(sensor)
{
}

void ConfigurationScreen::draw()
{
    setColor(WHITE, BLUE);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
    lcd.print("CONFIG");
    lcd.setCursor(0, 40);
    lcd.print("h:         mm");
    lcd.setTextSize(2);
    lcd.setCursor(0, 80);
    lcd.print("RAW:");
    lcd.setTextSize(3);
    lcd.setCursor(0, 110);
    lcd.print("UPPER:         mm");
    lcd.setCursor(0, 140);
    lcd.print("LOWER:         mm");

    lcd.setTextSize(2);
    lcd.setCursor(0, 180);
    lcd.print("Long press: Confirm\nShort press: Back");
    lcd.setCursor(130, 220);
    lcd.print("UPPER");
    lcd.setCursor(227, 220);
    lcd.print("LOWER");

    lcd.drawFastVLine(70, 220, 18, WHITE);
    lcd.drawLine(65, 232, 70, 238, WHITE);
    lcd.drawLine(75, 232, 70, 238, WHITE);
}

void ConfigurationScreen::update()
{
    lcd.setCursor(80, 40);
    lcd.setTextSize(4);
    lcd.printf("%6.2lf", sensor.convertedValue());
    lcd.setCursor(80, 80);
    lcd.setTextSize(2);
    lcd.printf("%5.2d", sensor.getRawValue());
    lcd.setTextSize(3);
    lcd.setCursor(120, 110);
    lcd.printf("%6.2lf", motorController.getUpperPosition());
    lcd.setCursor(120, 140);
    lcd.printf("%6.2lf", motorController.getLowerPosition());
}