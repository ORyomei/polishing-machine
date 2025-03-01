#ifndef _CONFIGURATION_SCREEN_H_
#define _CONFIGURATION_SCREEN_H_

#include "ui/screen.hpp"
#include "motor/motor_state_controller.hpp"
#include "config/configurator.hpp"

class ConfigurationScreen : public Screen
{
public:
    ConfigurationScreen(M5Display &lcd, MotorController &motorController, Configurator &Configurator, Sensor &sensor);
    void draw() override;
    void update() override;

private:
    MotorController &motorController;
    Configurator &configurator;
    Sensor &sensor;
};

#endif