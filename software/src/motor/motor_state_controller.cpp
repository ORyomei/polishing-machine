#include "motor_state_controller.hpp"

void MotorStateController::initialize()
{
    motorController->initialize();
    xTaskCreatePinnedToCore(startMotorRun, "MotorRun", 10000, motorController, 1, &motorRunTask, 1);
    xTaskCreatePinnedToCore(startReciprocalMotionControl, "MotorReciprocalMotionControl", 10000, motorController, 1, &motorReciprocalMotionTask, 0);
    xTaskCreatePinnedToCore(startMoveToStandbyPosition, "MoveToStandbyPosition", 10000, motorController, 1, &motorMoveToStandbyTask, 0);
    vTaskDelete(motorRunTask);
    vTaskDelete(motorReciprocalMotionTask);
    vTaskDelete(motorMoveToStandbyTask);

    xTaskCreatePinnedToCore(_waitForArrivalToStandby, "WaitForArrivalToStandby", 10000, this, 1, &waitForArrivalToStandbyTask, 0);
    vTaskDelete(waitForArrivalToStandbyTask);
    // setState(MotorState::OFF);
    setState(MotorSwitchState::OFF);
}

void MotorStateController::setState(MotorState motorState)
{
    if (this->motorState == motorState)
    {
        return;
    }
    // MotorState::OFF: None
    // MotorState::ON: motorRunTask, motorReciprocalMotionTask
    // MotorState::MOVE_TO_STANDBY: motorRunTask, motorMoveToStandbyTask
    if (this->motorState == MotorState::OFF && motorState == MotorState::ON)
    {
        Serial.println("MotorStateController: OFF -> ON");
        motorController->on();
        Serial.println("MotorStateController: Motor ON");
        xTaskCreatePinnedToCore(startMotorRun, "MotorRun", 10000, motorController, 1, &motorRunTask, 1);
        xTaskCreatePinnedToCore(startReciprocalMotionControl, "MotorReciprocalMotionControl", 10000, motorController, 1, &motorReciprocalMotionTask, 0);
    }
    else if (this->motorState == MotorState::OFF && motorState == MotorState::MOVE_TO_STANDBY)
    {
        motorController->on();
        xTaskCreatePinnedToCore(startMotorRun, "MotorRun", 10000, motorController, 1, &motorRunTask, 1);
        xTaskCreatePinnedToCore(startMoveToStandbyPosition, "MoveToStandbyPosition", 10000, motorController, 1, &motorMoveToStandbyTask, 0);
    }
    else if (this->motorState == MotorState::ON && motorState == MotorState::OFF)
    {
        motorController->off();
        vTaskDelete(motorRunTask);
        vTaskDelete(motorReciprocalMotionTask);
    }
    else if (this->motorState == MotorState::ON && motorState == MotorState::MOVE_TO_STANDBY)
    {
        vTaskDelete(motorReciprocalMotionTask);
        xTaskCreatePinnedToCore(startMoveToStandbyPosition, "MoveToStandbyPosition", 10000, motorController, 1, &motorMoveToStandbyTask, 0);
    }
    else if (this->motorState == MotorState::MOVE_TO_STANDBY && motorState == MotorState::OFF)
    {
        motorController->off();
        vTaskDelete(motorRunTask);
        vTaskDelete(motorMoveToStandbyTask);
    }
    else if (this->motorState == MotorState::MOVE_TO_STANDBY && motorState == MotorState::ON)
    {
        vTaskDelete(motorMoveToStandbyTask);
        xTaskCreatePinnedToCore(startReciprocalMotionControl, "MotorReciprocalMotionControl", 10000, motorController, 1, &motorReciprocalMotionTask, 0);
    }
    this->motorState = motorState;
}

void MotorStateController::setState(MotorSwitchState state)
{
    if (switchState == state)
    {
        return;
    }

    // MotorSwitchState::OFF: MotorState::OFF or MotorState::MOVE_TO_STANDBY
    // MotorSwitchState::ON: MotorState::ON
    // MotorSwitchState::EMERGENCY: MotorState::OFF

    if (switchState == MotorSwitchState::OFF && state == MotorSwitchState::ON)
    {
        if (eTaskGetState(waitForArrivalToStandbyTask) == eRunning)
        {
            vTaskDelete(waitForArrivalToStandbyTask);
        }
        setState(MotorState::ON);
    }
    else if (switchState == MotorSwitchState::OFF && state == MotorSwitchState::EMERGENCY)
    {
        if (eTaskGetState(waitForArrivalToStandbyTask) == eRunning)
        {
            vTaskDelete(waitForArrivalToStandbyTask);
        }
        setState(MotorState::OFF);
    }
    else if (switchState == MotorSwitchState::ON && state == MotorSwitchState::OFF)
    {
        setState(MotorState::MOVE_TO_STANDBY);
        xTaskCreatePinnedToCore(_waitForArrivalToStandby, "WaitForArrivalToStandby", 10000, this, 1, &waitForArrivalToStandbyTask, 0);
    }
    else if (switchState == MotorSwitchState::ON && state == MotorSwitchState::EMERGENCY)
    {
        setState(MotorState::OFF);
    }
    else if (switchState == MotorSwitchState::EMERGENCY && state == MotorSwitchState::OFF)
    {
    }
    else if (switchState == MotorSwitchState::EMERGENCY && state == MotorSwitchState::ON)
    {
        setState(MotorState::ON);
    }
    switchState = state;
}

void MotorStateController::waitForArrivalToStandby()
{
    while (true)
    {
        if (motorController->arrivedAtStandbyPosition())
        {
            setState(MotorState::OFF);
            vTaskDelete(NULL);
            break;
        }
        delay(1);
    }
}

void _waitForArrivalToStandby(void *motorStateController)
{
    ((MotorStateController *)motorStateController)->waitForArrivalToStandby();
}