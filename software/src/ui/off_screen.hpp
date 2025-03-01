#ifndef _OFF_SCREEN_H_
#define _OFF_SCREEN_H_

#include "screen.hpp"
#include "motor/motor_controller.hpp"
#include "sensor/sensor.hpp"

class OffScreen : public Screen
{
public:
    OffScreen(M5Display &lcd, MotorController &motorController, Sensor &sensor);
    void draw() override;
    void update() override;

private:
    MotorController &motorController;
    Sensor &sensor;
};

#endif