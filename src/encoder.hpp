#ifndef _ENCODER_H_
#define _ENCODER_H_
#include <Arduino.h>
#include <driver/pcnt.h>
#include "constants.hpp"

#define ENCODER_UNIT PCNT_UNIT_0
#define ENCODER_CHANNEL PCNT_CHANNEL_0

#define PCNT_CONFIG(pinA, pinB)       \
    {                                 \
        .pulse_gpio_num = pinA,       \
        .ctrl_gpio_num = pinB,        \
        .lctrl_mode = PCNT_MODE_KEEP, \
        .hctrl_mode = PCNT_MODE_KEEP, \
        .pos_mode = PCNT_COUNT_INC,   \
        .neg_mode = PCNT_COUNT_DIS,   \
        .counter_h_lim = 32767,       \
        .counter_l_lim = -32768,      \
        .unit = PCNT_UNIT_0,          \
        .channel = PCNT_CHANNEL_0,    \
    }

class Encoder
{
public:
    Encoder(uint8_t pinA = ENCODER_A_PIN, uint8_t pinB = ENCODER_B_PIN);
    void initialize();
    uint16_t getPosition();

private:
    pcnt_config_t config;
};

#endif