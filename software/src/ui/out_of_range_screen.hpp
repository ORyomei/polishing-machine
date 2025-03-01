#ifndef _OUT_OF_RANGE_SCREEN_H_
#define _OUT_OF_RANGE_SCREEN_H_

#include "screen.hpp"
#include "sensor/sensor.hpp"

class OutOfRangeScreen : public Screen
{
public:
    OutOfRangeScreen(M5Display &lcd, Sensor &sensor);
    void draw() override;
    void update() override;

private:
    Sensor &sensor;
};

#endif