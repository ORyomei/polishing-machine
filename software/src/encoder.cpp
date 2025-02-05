#include "encoder.hpp"

Encoder::Encoder(uint8_t pinA, uint8_t pinB) : config(PCNT_CONFIG(pinA, pinB))
{
}

void Encoder::initialize()
{
    pcnt_unit_config(&config);
    pcnt_counter_pause(config.unit);
    pcnt_counter_clear(config.unit);
    pcnt_counter_resume(config.unit);
}