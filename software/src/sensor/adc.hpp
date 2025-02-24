#ifndef _ADC_H_
#define _ADC_H_

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "gpio_interrupt.hpp"

// volatile bool existNewData;
// void IRAM_ATTR onAlertPinFall();

class Adc : public Adafruit_ADS1115
{
public:
    Adc(uint8_t alertPin = 4, uint8_t i2c_addr = ADS1X15_ADDRESS, TwoWire *wire = &Wire);
    void begin();
    int16_t read();
    int16_t getRawValue() { return rawValue; }
    bool hasNewData() { return alertInterrupt.interrupted(); }

private:
    uint8_t i2c_addr;
    TwoWire *wire;
    int16_t rawValue;
    GpioInterrupt alertInterrupt;
};

#endif