#include "adc.hpp"

Adc::Adc(uint8_t alertPin, uint8_t i2c_addr, TwoWire *wire) : i2c_addr(i2c_addr), wire(wire), alertInterrupt(alertPin, FALLING, INPUT) {}

void Adc::begin()
{
    alertInterrupt.begin();
    setGain(GAIN_TWOTHIRDS);
    setDataRate(RATE_ADS1115_475SPS);
    while (!Adafruit_ADS1115::begin(i2c_addr, wire))
        ;
    startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_0, true);
}

int16_t Adc::read()
{
    if (alertInterrupt.interrupted())
    {
        alertInterrupt.clear();
        rawValue = getLastConversionResults();
        return rawValue;
    }
    delay(1);
    return read();
}
