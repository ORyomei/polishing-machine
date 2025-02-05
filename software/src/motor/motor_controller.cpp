#include "motor_controller.hpp"

void MotorController::initialize()
{
    AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
    stepper.setMaxSpeed(1000);
}