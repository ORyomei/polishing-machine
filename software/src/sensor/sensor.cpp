#include "sensor.hpp"

Sensor::Sensor(uint16_t rawMinValue, uint16_t rawMaxValue, double minValue, double maxValue, double margin)
    : rawMinValue(rawMinValue), rawMaxValue(rawMaxValue), minValue(minValue), maxValue(maxValue), margin(margin)
{
    setConversion(minValue, maxValue);
}

void Sensor::setRawMin(uint16_t val)
{
    rawMinValue = val;
    setConversion();
}

void Sensor::setRawMax(uint16_t val)
{
    rawMaxValue = val;
    setConversion();
}

uint16_t Sensor::setCurrentValRawMin()
{
    rawMinValue = rawValue;
    setConversion();
    return rawMinValue;
}

uint16_t Sensor::setCurrentValRawMax()
{
    rawMaxValue = rawValue;
    setConversion();
    return rawMaxValue;
}

void Sensor::setConversion(double minValue, double maxValue)
{
    this->slope = (maxValue - minValue) / (rawMaxValue - rawMinValue);
    this->intercept = (rawMaxValue * minValue - rawMinValue * maxValue) / (rawMaxValue - rawMinValue);
}

void Sensor::setConversion()
{
    this->slope = (maxValue - minValue) / (rawMaxValue - rawMinValue);
    this->intercept = (rawMaxValue * minValue - rawMinValue * maxValue) / (rawMaxValue - rawMinValue);
}

double Sensor::convertedValue()
{
    return rawValue * slope + intercept;
}

bool Sensor::isInRange()
{
    double value = convertedValue();
    if (value < minValue - margin || value > maxValue + margin)
    {
        return false;
    }
    return true;
}

double Sensor::getMaxValue()
{
    return maxValue;
}

double Sensor::getMinValue()
{
    return minValue;
}

uint16_t Sensor::getRawValue()
{
    return rawValue;
}
