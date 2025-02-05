#ifndef _SIN_H_
#define _SIN_H_
#include <Arduino.h>

#define FAST_SIN_TABLE_SIZE 256

class FastSin
{
public:
    FastSin();
    double get(uint16_t index);

private:
    double table[FAST_SIN_TABLE_SIZE];
};

#endif