#ifndef _VIBRATOR_H_
#define _VIBRATOR_H_

#include "config/constants.hpp"
#include <Arduino.h>

class Vibrator
{
public:
    Vibrator(uint8_t pin = VIBRATOR_PIN);
    void initialize();
    void on();
    void off();

private:
    uint8_t pin;
};

#endif
