#ifndef _MOTOR_CONTROOLER_H_
#define _MOTOR_CONTROOLER_H_
#include <Arduino.h>
#include <AccelStepper.h>
#include "constants.hpp"

#define MOTOR_CONTROL_CYLCLE_TIME 30 // ms

class MotorController
{
public:
    void initialize();

private:
};

#endif