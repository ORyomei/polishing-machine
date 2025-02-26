#ifndef _SOLENOID_CONTROLLER_H_
#define _SOLENOID_CONTROLLER_H_
#include "config/constants.hpp"
#include <Arduino.h>

class SolenoidController
{
public:
    SolenoidController();
    void initialize();
    void setDuty(double duty);
    void setFrequency(double frequency);
    void enable(bool enable = true);
    void cycle(bool enable);
    void run();

private:
    uint8_t pin = VIBRATOR_PIN;
    double duty = SOLENOID_DUTY;
    double frequency;
    bool state;
    bool enabled;
    uint16_t on_time, off_time;
    void on();
    void off();
};

void startSolenoid(void *solenoidController);

#endif