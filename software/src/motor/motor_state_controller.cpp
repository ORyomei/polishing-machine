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
    setState(MotorState::OFF);
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

// void MotorStateController::setState(MotorSwitchState motorSwitchState)
// {
//     if (this->motorSwitchState == motorSwitchState)
//     {
//         return;
//     }

//     // MotorSwitchState::OFF: MotorState::OFF or MotorState::MOVE_TO_STANDBY
//     // MotorSwitchState::ON: MotorState::ON
//     // MotorSwitchState::EMERGENCY: MotorState::OFF

//     if (this->motorSwitchState == MotorSwitchState::OFF && motorSwitchState == MotorSwitchState::ON)
//     {
//         setState(MotorState::ON);
//     }
//     else if (this->motorSwitchState == MotorSwitchState::ON && motorSwitchState == MotorSwitchState::OFF)
//     {
//         setState(MotorState::OFF);
//     }
//     else if (this->motorSwitchState == MotorSwitchState::ON && motorSwitchState == MotorSwitchState::EMERGENCY)
//     {
//         setState(MotorState::MOVE_TO_STANDBY);
//     }
// }