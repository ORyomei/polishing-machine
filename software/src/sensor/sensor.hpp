#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#define SENSOR_MIN 0.0
#define SENSOR_MAX 100.0

class Sensor
{
public:
    Sensor(uint16_t rawMinValue, uint16_t rawMaxValue, double minValue, double maxValue, double margin);
    virtual void read() = 0;
    void setConversion(double minValue, double maxValue);
    void setConversion();
    void setRawMin(uint16_t val);
    void setRawMax(uint16_t val);
    uint16_t setCurrentValRawMin();
    uint16_t setCurrentValRawMax();
    double convertedValue();
    bool isInRange();
    double getMaxValue();
    double getMinValue();
    uint16_t getRawValue();

protected:
    uint16_t rawValue;
    uint16_t rawMinValue, rawMaxValue;
    const double minValue, maxValue;
    const double margin;
    double intercept, slope;
};

#endif