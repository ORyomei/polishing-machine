#include "sin.hpp"

FastSin::FastSin()
{
    for (uint16_t i = 0; i < FAST_SIN_TABLE_SIZE; i++)
    {
        table[i] = 0.5 * sin(2 * PI * i / FAST_SIN_TABLE_SIZE) + 0.5;
    }
}

double FastSin::get(uint16_t index)
{
    index = index % FAST_SIN_TABLE_SIZE;
    return table[index];
}