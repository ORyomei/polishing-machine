#ifndef _MOTOR_STATE_CONTROLLER_H_
#define _MOTOR_STATE_CONTROLLER_H_

#include <Arduino.h>
#include "motor_controller.hpp"
#include "motor_state.hpp"

class MotorStateController
{
public:
    MotorStateController(MotorController *motorController) : motorController(motorController) {}
    void initialize();
    void setState(MotorSwitchState state);

private:
    TaskHandle_t motorRunTask, motorReciprocalMotionTask, motorMoveToStandbyTask;
    MotorController *motorController;
    MotorState motorState = MotorState::OFF;
    MotorSwitchState motorSwitchState = MotorSwitchState::OFF;
    void setState(MotorState state);
};

#endif