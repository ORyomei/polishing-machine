#ifndef _MOTOR_CONTROOLER_H_
#define _MOTOR_CONTROOLER_H_
#include <Arduino.h>
#include <AccelStepper.h>
#include "constants.hpp"
#include "sensor/sensor.hpp"

#define MOTOR_CONTROL_CYLCLE_TIME 30 // ms
#define MOTOR_MAX_SPEED 3000
#define MOTOR_ACCELERATION 2000

#define POSITION_TO_MOTOR_STEPS_COEFFICIENT 842.105

class MotorController
{
public:
    MotorController(Sensor &sensor) : sensor(sensor) {}
    void initialize();
    void on();
    void off();
    void startMotorRun();
    void startReciprocalMotionControl();
    void moveToStanbyPosition();
    // void moveToUpperPosition();
    // void moveToLowerPosition();

private:
    double upperPosition, lowerPosition, standbyPosition;
    bool isOn;
    bool arrived = false;
    uint8_t enablePin = STEPPER_ENABLE_PIN;
    AccelStepper stepper = AccelStepper(AccelStepper::FULL2WIRE, STEPPER_STEP_PIN, STEPPER_DIR_PIN);
    Sensor &sensor;
};

void startMotorRun(void *motorController);

void startReciprocalMotionControl(void *motorController);

void startMoveToStandbyPosition(void *motorController);

#endif