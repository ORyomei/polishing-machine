#ifndef _GPIO_INTERRUPT_H_
#define _GPIO_INTERRUPT_H_
#include <Arduino.h>

class GpioInterrupt
{
public:
    GpioInterrupt(uint8_t pin, uint8_t mode, uint8_t pinMode);
    void begin();
    bool interrupted();
    void clear();

private:
    uint8_t pin;
    uint8_t mode;
    uint8_t pinMode_;
    static volatile bool _interrupted;
    static void IRAM_ATTR onInterrupt();
};

#endif