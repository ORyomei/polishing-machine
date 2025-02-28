#ifndef _UI_H_
#define _UI_H_

#include "motor/motor_state_controller.hpp"
#include "config/configurator.hpp"
#include <M5Display.h>

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
    UI(Sensor &sensor, MotorStateController &motorStateController, Configurator &configurator) : sensor(sensor), motorStateController(motorStateController), configurator(configurator) {}
    void initialize();
    void run();
    void start();

private:
    TaskHandle_t taskHandle;
    M5Display lcd;
    Sensor &sensor;
    MotorStateController &motorStateController;
    Configurator &configurator;
    UIMode mode;
    UIMode getMode();
    void update();
    void (UI::*setData)() = nullptr;

    void drawConfiguratingBackGround();
    void drawRunningBackGround();
    void drawEmergencyBackGround();
    void drawOutOfRangeBackGround();
    void drawOffBackGround();

    // void setData(UIMode mode);
    void setConfiguratingData();
    void setRunningData();
    void setEmergencyData();
    void setOutOfRangeData();
    void setOffData();
};

const char *UIModeToString(UIMode mode);

void runUI(void *ui);

#endif