#include "gpio_interrupt.hpp"

GpioInterrupt::GpioInterrupt(uint8_t pin, uint8_t mode, uint8_t pinMode) : pin(pin), mode(mode), pinMode_(pinMode) {}

void GpioInterrupt::begin()
{
    pinMode(pin, pinMode_);
    attachInterrupt(digitalPinToInterrupt(pin), onInterrupt, mode);
}

bool GpioInterrupt::interrupted()
{
    return _interrupted;
}

void GpioInterrupt::clear()
{
    _interrupted = false;
}

volatile bool GpioInterrupt::_interrupted = false;

void IRAM_ATTR GpioInterrupt::onInterrupt()
{
    _interrupted = true;
}