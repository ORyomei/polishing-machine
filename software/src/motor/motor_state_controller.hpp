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
    void waitForArrivalToStandby();
    void off();
    bool motorRunning();
    bool movingToStandby();

    MotorState getMotorState() { return motorState; }
    MotorSwitchState getSwitchState() { return switchState; }

private:
    TaskHandle_t motorRunTask, motorReciprocalMotionTask, motorMoveToStandbyTask;
    TaskHandle_t waitForArrivalToStandbyTask;
    MotorController *motorController;
    MotorState motorState = MotorState::OFF;
    MotorSwitchState switchState = MotorSwitchState::OFF;
    void setState(MotorState state);
};

void _waitForArrivalToStandby(void *motorStateController);

#endif