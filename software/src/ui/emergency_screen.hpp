#ifndef _EMERGENCY_SCREEN_H_
#define _EMERGENCY_SCREEN_H_

#include "screen.hpp"

class EmergencyScreen : public Screen
{
public:
    EmergencyScreen(M5Display &lcd) : Screen(lcd) {}
    void draw() override;
    void update() override;
};

#endif