#include "vibrator.hpp"

Vibrator::Vibrator(uint8_t pin) : pin(pin)
{
}

void Vibrator::initialize()
{
    pinMode(pin, OUTPUT);
    off();
}

void Vibrator::on()
{
    digitalWrite(pin, HIGH);
}

void Vibrator::off()
{
    digitalWrite(pin, LOW);
}