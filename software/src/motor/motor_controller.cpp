#include "motor_controller.hpp"

MotorController::MotorController(Sensor &sensor) : sensor(sensor)
{
    standbyPosition = STANDBY_POSITION;
}

void MotorController::initialize()
{
    stepper.setEnablePin(enablePin);
    stepper.setPinsInverted(false, false, true);
    stepper.setMaxSpeed(MOTOR_MAX_SPEED);
    stepper.setAcceleration(MOTOR_ACCELERATION);
    off();
}

void MotorController::on()
{
    Serial.println("MotorController::on()");
    stepper.enableOutputs();
    isOn = true;
}

void MotorController::off()
{
    Serial.println("MotorController::off()");
    stepper.disableOutputs();
    isOn = false;
}

void MotorController::startMotorRun()
{
    while (true)
    {
        stepper.run();
        if (stepper.distanceToGo() == 0)
        {
            arrived = true;
        }
    }
}

void MotorController::startReciprocalMotionControl()
{
    while (true)
    {
        double currentPosition = sensor.convertedValue();
        double targetPosition = upperPosition;
        int steps = (targetPosition - currentPosition) * POSITION_TO_MOTOR_STEPS_COEFFICIENT;
        stepper.moveTo(stepper.currentPosition() + steps);
        arrived = false;
        while (!arrived)
        {
            delay(MOTOR_CONTROL_CYLCLE_TIME);
        }
        Serial.println("Arrived at upper position");
        currentPosition = sensor.convertedValue();
        targetPosition = lowerPosition;
        steps = (targetPosition - currentPosition) * POSITION_TO_MOTOR_STEPS_COEFFICIENT;
        stepper.moveTo(stepper.currentPosition() + steps);
        arrived = false;
        while (!arrived)
        {
            delay(MOTOR_CONTROL_CYLCLE_TIME);
        }
        Serial.println("Arrived at lower position");
    }
}

void MotorController::moveToStanbyPosition()
{
    double currentPosition = sensor.convertedValue();
    double targetPosition = standbyPosition;
    int steps = (targetPosition - currentPosition) * POSITION_TO_MOTOR_STEPS_COEFFICIENT;
    stepper.moveTo(stepper.currentPosition() + steps);
    arrived = false;
    arrivedAtStandby = false;
    while (true)
    {
        if (arrived)
        {
            break;
        }
        delay(MOTOR_CONTROL_CYLCLE_TIME);
    }
    arrivedAtStandby = true;
    while (true)
    {
        delay(MOTOR_CONTROL_CYLCLE_TIME);
    }
}

void startMotorRun(void *motorController)
{
    MotorController *controller;
    controller = (MotorController *)motorController;
    controller->startMotorRun();
}

void startReciprocalMotionControl(void *motorController)
{
    MotorController *controller;
    controller = (MotorController *)motorController;
    controller->startReciprocalMotionControl();
}

void startMoveToStandbyPosition(void *motorController)
{
    MotorController *controller;
    controller = (MotorController *)motorController;
    controller->moveToStanbyPosition();
}