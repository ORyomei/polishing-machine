#ifndef _STEPPER_H_
#define _STEPPER_H_

#include <AccelStepper.h>

class Stepper : public AccelStepper
{
public:
    Stepper(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool enable = false) : AccelStepper(interface, pin1, pin2, pin3, pin4, enable) {}
    void step1(long step);
    void setOutputPins(uint8_t mask);

private:
    uint8_t _pinMask;
};

#endif
