#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <M5Display.h>

class Screen
{
public:
    Screen(M5Display &lcd) : lcd(lcd) {}
    void setColor(uint16_t fgColor, uint16_t bgColor);
    virtual void draw() {};
    virtual void update() {};

protected:
    M5Display &lcd;

    const int16_t lcdWidth = 320;
    const int16_t lcdHeight = 240;
};

#endif