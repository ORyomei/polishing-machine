#ifndef _UI_H_
#define _UI_H_

#include "motor/motor_state_controller.hpp"
#include "config/configurator.hpp"
#include <M5Display.h>
#include "screen.hpp"
#include "configuration_screen.hpp"
#include "emergency_screen.hpp"
#include "out_of_range_screen.hpp"
#include "running_screen.hpp"
#include "off_screen.hpp"

#define LCD_UPDATE_INTERVAL 50

enum class UIMode
{
    CONFIGURATING,
    EMERGENCY,
    OUT_OF_RANGE,
    RUNNING,
    OFF
};
class UI
{
public:
    UI(Sensor &sensor, MotorStateController &motorStateController, MotorController &motorController, Configurator &configurator);
    void initialize();
    void run();
    void start();

private:
    TaskHandle_t taskHandle;
    M5Display lcd;
    Sensor &sensor;
    MotorStateController &motorStateController;
    MotorController &motorController;
    Configurator &configurator;
    UIMode mode;

    ConfigurationScreen configurationScreen;
    EmergencyScreen emergencyScreen;
    OutOfRangeScreen outOfRangeScreen;
    RunningScreen runningScreen;
    OffScreen offScreen;

    Screen *currentScreen = nullptr;

    UIMode getMode();
    void update();
};

const char *UIModeToString(UIMode mode);

void runUI(void *ui);

#endif