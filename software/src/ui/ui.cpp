#include "ui.hpp"

UI::UI(Sensor &sensor, MotorStateController &motorStateController, MotorController &motorController, Configurator &configurator, MachineStateController &machineStateController)
    : sensor(sensor), motorStateController(motorStateController), motorController(motorController), configurator(configurator), machineStateController(machineStateController),
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
    MachineState state = machineStateController.getState();
    if (state != this->state || currentScreen == nullptr)
    {
        this->state = state;
        switch (state)
        {
        case MachineState::CONFIGURATING:
            currentScreen = &configurationScreen;
            break;
        case MachineState::EMERGENCY:
            currentScreen = &emergencyScreen;
            break;
        case MachineState::OUT_OF_RANGE:
            currentScreen = &outOfRangeScreen;
            break;
        case MachineState::RUNNING:
            currentScreen = &runningScreen;
            break;
        case MachineState::OFF:
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

void runUI(void *ui)
{
    ((UI *)ui)->run();
}