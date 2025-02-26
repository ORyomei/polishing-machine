#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include "adc.hpp"

#define SENSOR_MIN 0.0   // mm
#define SENSOR_MAX 128.0 // mm

// TODO change
#define SENSOR_LOWER_LIMIT 10.0  // mm
#define SENSOR_UPPER_LIMIT 115.0 // mm

#define SENSOR_RAW_MIN 0
#define SENSOR_RAW_MAX 20000

#define SENSOR_IN_RANGE_PERIOD 100 // ms

class InRangeChecker
{
public:
    InRangeChecker(double lowerLimit, double upperLimit) : lowerLimit(lowerLimit), upperLimit(upperLimit) {}
    bool isInRangeForPeriod(double value)
    {
        unsigned long now = millis();
        if (lastInRangeTime == 0)
        {
            lastInRangeTime = now;
            return true;
        }
        if (lowerLimit <= value && value <= upperLimit)
        {
            lastInRangeTime = now;
            return true;
        }
        if (now - lastInRangeTime > SENSOR_IN_RANGE_PERIOD)
        {
            return false;
        }
        return true;
    }

private:
    double lowerLimit, upperLimit;
    unsigned long lastInRangeTime = 0;
};

class Sensor
{
public:
    Sensor(int16_t rawMinValue = SENSOR_RAW_MIN, int16_t rawMaxValue = SENSOR_RAW_MAX, double minValue = SENSOR_MIN, double maxValue = SENSOR_MAX, double lowerLimit = SENSOR_LOWER_LIMIT, double upperLimit = SENSOR_UPPER_LIMIT);
    void initialize();
    void read();
    void setConversion(double minValue, double maxValue);
    void setConversion();
    void setRawMin(int16_t val);
    void setRawMax(int16_t val);
    int16_t setCurrentValRawMin();
    int16_t setCurrentValRawMax();
    double convertedValue();
    bool isInRange();
    double getMaxValue();
    double getMinValue();
    int16_t getRawValue();

protected:
    Adc adc;
    int16_t rawValue;
    int16_t rawMinValue, rawMaxValue;
    const double lowerLimit, upperLimit;
    const double minValue, maxValue;
    double intercept, slope;
    InRangeChecker inRangeChecker;
};

#endif