#ifndef _RUNNING_SCREEN_H_
#define _RUNNING_SCREEN_H_

#include "screen.hpp"
#include "motor/motor_state_controller.hpp"
#include "sensor.h"

class RunningScreen : public Screen
{
public:
    RunningScreen(M5Display &lcd, MotorStateController &motorStateController, MotorController &motoController, Sensor &sensor);
    void draw() override;
    void update() override;

private:
    MotorStateController &motorStateController;
    MotorController &motorController;
    Sensor &sensor;
};

#endif