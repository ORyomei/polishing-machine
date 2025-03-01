#include "stepper.hpp"

void Stepper::setOutputPins(uint8_t mask)
{
    _pinMask = mask;
    AccelStepper::setOutputPins(mask);
}

void Stepper::step1(long step)
{
    (void)(step); // Unused

    // _pin[0] is step, _pin[1] is direction
    uint8_t dir = _direction == DIRECTION_CW ? 0b10 : 0b00;
    setOutputPins(dir | (_pinMask & 0b01));          // Set direction first else get rogue pulses
    setOutputPins((dir | (_pinMask & 0b01)) ^ 0b01); // step HIGH
}