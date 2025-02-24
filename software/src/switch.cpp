#include "switch.hpp"

ToggleSwitch::ToggleSwitch(uint8_t pin) : pin(pin) {}

void ToggleSwitch::initialize()
{
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    lastState = state;
    _isOn = state == onState;
    _switched = false;
}

void ToggleSwitch::read()
{
    lastState = state;
    state = digitalRead(pin);
    lastTime = time;
    time = millis();
    if (state != lastState)
    {
        lastChange = time;
    }
    if ((time - lastChange > duration) && ((state == onState) != _isOn))
    {
        _isOn = (state == onState);
        _switched = true;
    }
    else
    {
        _switched = false;
    }
}

bool ToggleSwitch::isOn()
{
    return _isOn;
}

bool ToggleSwitch::switched()
{
    return _switched;
}

bool ToggleSwitch::switchedToOn()
{
    return _switched && _isOn;
}

bool ToggleSwitch::switchedToOff()
{
    return _switched && !_isOn;
}

MotorSwitch::MotorSwitch(uint8_t fwdPin, uint8_t revPin) : fwdToggleSwitch(fwdPin), revToggleSwitch(revPin) {}

void MotorSwitch::initialize()
{
    fwdToggleSwitch.initialize();
    revToggleSwitch.initialize();
}

void MotorSwitch::read()
{
    fwdToggleSwitch.read();
    revToggleSwitch.read();
}

bool MotorSwitch::changed()
{
    return fwdToggleSwitch.switched() || revToggleSwitch.switched();
}

MotorSwitchState MotorSwitch::getState()
{
    if (fwdToggleSwitch.isOn() && revToggleSwitch.isOn())
    {
        return MotorSwitchState::EMERGENCY;
    }
    else if (fwdToggleSwitch.isOn())
    {
        return MotorSwitchState::ON;
    }
    else if (!revToggleSwitch.isOn())
    {
        return MotorSwitchState::OFF;
    }
    return MotorSwitchState::OFF;
}