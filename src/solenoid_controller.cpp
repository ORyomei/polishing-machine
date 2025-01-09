#include "solenoid_controller.hpp"

SolenoidController::SolenoidController()
{
}

void SolenoidController::initialize()
{
    pinMode(pin, OUTPUT);
    off();
    setFrequency(SOLENOID_DEFAULT_FREQUENCY);
}

void SolenoidController::setDuty(double duty)
{
    this->duty = constrain(duty, 0.0, 1.0);
}

void SolenoidController::setFrequency(double frequency)
{
    this->frequency = frequency;
    on_time = 1000 / frequency * duty;
    off_time = 1000 / frequency * (1 - duty);
}

void SolenoidController::enable(bool enable)
{
    this->enabled = enable;
}

void SolenoidController::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void SolenoidController::off()
{
    state = false;
    digitalWrite(pin, LOW);
}

void SolenoidController::cycle(bool state)
{
    if (state)
    {
        on();
        delay(on_time);
        off();
        delay(off_time);
    }
    else
    {
        off();
        delay(on_time + off_time);
    }
}

void SolenoidController::run()
{
    while (true)
    {
        cycle(enabled);
    }
}

void startSolenoid(void *solenoidController)
{
    ((SolenoidController *)solenoidController)->run();
}