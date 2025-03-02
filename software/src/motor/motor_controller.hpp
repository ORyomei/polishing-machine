#ifndef _MOTOR_CONTROOLER_H_
#define _MOTOR_CONTROOLER_H_
#include <Arduino.h>
#include "stepper.hpp"
#include "config/constants.hpp"
#include "sensor/sensor.hpp"

#define MOTOR_CONTROL_CYLCLE_TIME 59 // ms
#define MOTOR_MAX_SPEED 57600
#define MOTOR_ACCELERATION 64000

#define POSITION_TO_MOTOR_STEPS_COEFFICIENT 12500

class MotorController
{
public:
    MotorController(Sensor &sensor);
    void initialize();
    void on();
    void off();
    void startMotorRun();
    void startReciprocalMotionControl();
    void moveToStanbyPosition();
    bool arrivedAtStandbyPosition() { return arrivedAtStandby; }

    void setUpperPosition(double position) { upperPosition = position; }
    void setLowerPosition(double position) { lowerPosition = position; }
    double getUpperPosition() { return upperPosition; }
    double getLowerPosition() { return lowerPosition; }

private:
    double upperPosition,
        lowerPosition,
        standbyPosition;
    bool isOn;
    bool arrived = false;
    bool arrivedAtStandby = false;
    uint8_t enablePin = STEPPER_ENABLE_PIN;
    Stepper stepper = Stepper(Stepper::DRIVER, STEPPER_STEP_PIN, STEPPER_DIR_PIN, -1, -1, false);
    Sensor &sensor;
};

void startMotorRun(void *motorController);

void startReciprocalMotionControl(void *motorController);

void startMoveToStandbyPosition(void *motorController);

#endif
