#include "ui.hpp"

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
    // Serial.printf("UIMode: %s\n", UIModeToString(mode));
    if (mode != this->mode || setData == nullptr)
    {
        Serial.printf("UIMode changed: %s\n", UIModeToString(mode));
        this->mode = mode;
        switch (mode)
        {
        case UIMode::CONFIGURATING:
            drawConfiguratingBackGround();
            setData = &UI::setConfiguratingData;
            break;
        case UIMode::EMERGENCY:
            drawEmergencyBackGround();
            setData = &UI::setEmergencyData;
            break;
        case UIMode::OUT_OF_RANGE:
            drawOutOfRangeBackGround();
            setData = &UI::setOutOfRangeData;
            break;
        case UIMode::RUNNING:
            drawRunningBackGround();
            setData = &UI::setRunningData;
            break;
        case UIMode::OFF:
            drawOffBackGround();
            setData = &UI::setOffData;
            break;
        default:
            break;
        }
    }
    (this->*setData)();
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

void UI::drawConfiguratingBackGround()
{
    lcd.fillScreen(BLUE);
    lcd.setCursor(0, 0);
    lcd.setTextSize(4);
    lcd.setTextColor(WHITE, BLUE);
    lcd.printf("Configurating");
}

void UI::drawRunningBackGround()
{
    lcd.fillScreen(BLACK);
    lcd.setCursor(0, 0);
    lcd.setTextSize(4);
    lcd.setTextColor(WHITE, BLACK);
    lcd.printf("Running");
}

void UI::drawEmergencyBackGround()
{
    lcd.fillScreen(RED);
    lcd.setCursor(0, 0);
    lcd.setTextSize(4);
    lcd.setTextColor(WHITE, RED);
    lcd.printf("Emergency");
}

void UI::drawOutOfRangeBackGround()
{
    lcd.fillScreen(RED);
    lcd.setCursor(0, 0);
    lcd.setTextSize(4);
    lcd.setTextColor(WHITE, RED);
    lcd.printf("Out of Range");
}

void UI::drawOffBackGround()
{
    lcd.fillScreen(BLACK);
    lcd.setCursor(0, 0);
    lcd.setTextSize(4);
    lcd.setTextColor(WHITE, BLACK);
    lcd.printf("Off");
}

void UI::setConfiguratingData()
{
    // Serial.println("Set Configurating Data");
    lcd.setCursor(0, 40);
    lcd.setTextSize(4);
    lcd.printf("h: %6.2lf mm", sensor.convertedValue());
    lcd.setCursor(0, 80);
    lcd.setTextSize(2);
    lcd.printf("Raw: %6.2d", sensor.getRawValue());
    // Serial.printf("h: %6.2lf mm\n", sensor.convertedValue());
}

void UI::setRunningData()
{
}

void UI::setEmergencyData()
{
}

void UI::setOutOfRangeData()
{
}

void UI::setOffData()
{
}

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