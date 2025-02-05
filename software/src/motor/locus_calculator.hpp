#ifndef _LOCUS_CALCULATOR_H_
#define _LOCUS_CALCULATOR_H_

#include <Arduino.h>
#include "sin.hpp"

class LocusCalculator
{
public:
    LocusCalculator();
    double calculateNextPosition();
    void setFrequency(double frequency);
    void setCycleTime(uint32_t cycleTime);

private:
    FastSin sin;
    double frequency;
    uint32_t currentCount;
    uint32_t cycleTime;
};

#endif