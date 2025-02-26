#include "sensor.hpp"

Sensor::Sensor(int16_t rawMinValue, int16_t rawMaxValue, double minValue, double maxValue, double lowerLimit, double upperLimit)
    : rawMinValue(rawMinValue), rawMaxValue(rawMaxValue), minValue(minValue), maxValue(maxValue), lowerLimit(lowerLimit), upperLimit(upperLimit), inRangeChecker(lowerLimit, upperLimit)
{
    setConversion(minValue, maxValue);
}

void Sensor::initialize()
{
    adc.begin();
}

void Sensor::setRawMin(int16_t val)
{
    rawMinValue = val;
    setConversion();
}

void Sensor::setRawMax(int16_t val)
{
    rawMaxValue = val;
    setConversion();
}

int16_t Sensor::setCurrentValRawMin()
{
    rawMinValue = rawValue;
    setConversion();
    return rawMinValue;
}

int16_t Sensor::setCurrentValRawMax()
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
    return inRangeChecker.isInRangeForPeriod(value);
}

double Sensor::getMaxValue()
{
    return maxValue;
}

double Sensor::getMinValue()
{
    return minValue;
}

int16_t Sensor::getRawValue()
{
    return rawValue;
}

void Sensor::read()
{
    rawValue = adc.read();
}