#include "ui.hpp"

UI::UI(Sensor &sensor, MotorStateController &motorStateController, MotorController &motorController, Configurator &configurator)
    : sensor(sensor), motorStateController(motorStateController), motorController(motorController), configurator(configurator),
      configurationScreen(lcd, motorController, configurator, sensor),
      emergencyScreen(lcd),
      outOfRangeScreen(lcd, sensor),
      runningScreen(lcd, motorStateController, motorController, sensor),
      offScreen(lcd, motorController, sensor)
{
}

void UI::initialize()
{
    lcd.begin();
    lcd.fillScreen(BLACK);
    lcd.setTextColor(WHITE);
    lcd.setTextSize(4);
    lcd.setCursor(0, 0);
}

void UI::update()
{
    UIMode mode = getMode();
    if (mode != this->mode || currentScreen == nullptr)
    {
        Serial.printf("UIMode changed: %s\n", UIModeToString(mode));
        this->mode = mode;
        switch (mode)
        {
        case UIMode::CONFIGURATING:
            currentScreen = &configurationScreen;
            break;
        case UIMode::EMERGENCY:
            currentScreen = &emergencyScreen;
            break;
        case UIMode::OUT_OF_RANGE:
            currentScreen = &outOfRangeScreen;
            break;
        case UIMode::RUNNING:
            currentScreen = &runningScreen;
            break;
        case UIMode::OFF:
            currentScreen = &offScreen;
            break;
        default:
            break;
        }
        currentScreen->draw();
    }
    currentScreen->update();
}

void UI::run()
{
    while (true)
    {
        update();
        delay(LCD_UPDATE_INTERVAL);
    }
}

void UI::start()
{
    xTaskCreatePinnedToCore(runUI, "UI", 8192, this, 2, &taskHandle, 0);
}

UIMode UI::getMode()
{
    if (!sensor.isInRange())
    {
        return UIMode::OUT_OF_RANGE;
    }
    if (motorStateController.getSwitchState() == MotorSwitchState::EMERGENCY)
    {
        return UIMode::EMERGENCY;
    }
    if (configurator.enabled())
    {
        return UIMode::CONFIGURATING;
    }
    if (motorStateController.motorRunning())
    {
        return UIMode::RUNNING;
    }
    if (motorStateController.getMotorState() == MotorState::OFF)
    {
        return UIMode::OFF;
    }
    return UIMode::EMERGENCY;
}

// void UI::drawConfiguratingBackGround()
// {
//     setColor(WHITE, BLUE);
//     lcd.setCursor(0, 0);
//     lcd.setTextSize(4);
//     lcd.printf("CONFIG");
//     drawFooter("Confirm", "Upper", "Lower");
// }

// void UI::drawRunningBackGround()
// {
//     lcd.fillScreen(GREEN);
//     lcd.setCursor(0, 0);
//     lcd.setTextSize(4);
//     lcd.setTextColor(WHITE, GREEN);
//     lcd.printf("Running");
// }

// void UI::drawEmergencyBackGround()
// {
//     lcd.fillScreen(RED);
//     lcd.setCursor(0, 0);
//     lcd.setTextSize(4);
//     lcd.setTextColor(WHITE, RED);
//     lcd.printf("Emergency");
// }

// void UI::drawOutOfRangeBackGround()
// {
//     lcd.fillScreen(RED);
//     lcd.setCursor(0, 0);
//     lcd.setTextSize(4);
//     lcd.setTextColor(WHITE, RED);
//     lcd.printf("Out of Range");
// }

// void UI::drawOffBackGround()
// {
//     lcd.fillScreen(BLACK);
//     lcd.setCursor(0, 0);
//     lcd.setTextSize(4);
//     lcd.setTextColor(WHITE, BLACK);
//     lcd.printf("Off");
// }

// void UI::setConfiguratingData()
// {
//     // Serial.println("Set Configurating Data");
//     lcd.setCursor(0, 40);
//     lcd.setTextSize(4);
//     lcd.printf("h: %6.2lf mm", sensor.convertedValue());
//     lcd.setCursor(0, 80);
//     lcd.setTextSize(2);
//     lcd.printf("Raw: %6.2d", sensor.getRawValue());
//     // Serial.printf("h: %6.2lf mm\n", sensor.convertedValue());
// }

// void UI::setRunningData()
// {
// }

// void UI::setEmergencyData()
// {
// }

// void UI::setOutOfRangeData()
// {
// }

// void UI::setOffData()
// {
// }

// void UI::drawFooter(const char *a, const char *b, const char *c)
// {
//     lcd.drawRect(0, footerCursorY, lcdWidth, lcdHeight, WHITE);
//     lcd.drawFastVLine(footerSeparatorX[0], footerCursorY, footerHeight, WHITE);
//     lcd.drawFastVLine(footerSeparatorX[1], footerCursorY, footerHeight, WHITE);
//     lcd.setTextSize(footerTextSize);
//     lcd.setCursor(footerCursorX[0], footerCursorY + footerCursorShiftY);
//     lcd.print(a);
//     lcd.setCursor(footerCursorX[1], footerCursorY + footerCursorShiftY);
//     lcd.print(b);
//     lcd.setCursor(footerCursorX[2], footerCursorY + footerCursorShiftY);
//     lcd.print(c);
// }

const char *UIModeToString(UIMode mode)
{
    switch (mode)
    {
    case UIMode::CONFIGURATING:
        return "Configurating";
    case UIMode::EMERGENCY:
        return "Emergency";
    case UIMode::OUT_OF_RANGE:
        return "Out of Range";
    case UIMode::RUNNING:
        return "Running";
    case UIMode::OFF:
        return "Off";
    default:
        return "Unknown";
    }
}

void runUI(void *ui)
{
    ((UI *)ui)->run();
}