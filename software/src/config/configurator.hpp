#ifndef _CONFIGURATOR_H_
#define _CONFIGURATOR_H_

#include <Arduino.h>
#include "flash.hpp"
#include "motor/motor_controller.hpp"
#include "sensor/sensor.hpp"
#include <utility/Button.h>
#include <utility/Config.h>
#include <ArduinoJson.h>

#define UPPER_LOWER_POSITION_FILE_NAME "/upper_lower_position.txt"

struct Config
{
public:
    virtual bool loadFromJsonStr(const char *jsonStr);
    virtual void loadFromConstants();
    virtual const char *toJsonStr();
};

struct UpperLowerPositionConfig : Config
{
    double upperPosition;
    double lowerPosition;
    bool loadFromJsonStr(const char *jsonStr);
    void loadFromConstants();
    const char *toJsonStr();
};

class Configurator
{
public:
    Configurator(MotorController &motorController, Sensor &sensor) : motorController(motorController),
                                                                     sensor(sensor) {}
    void initialize();
    void loadUpperLowerPositionFromFlash();
    void calibrateFromflash();
    void enable();
    void disable();
    void setCurrentPositionUpper();
    void setCurrentPositionLower();

    void start();
    void run();

private:
    Flash flash;
    MotorController &motorController;
    Sensor &sensor;
    UpperLowerPositionConfig upperLowerPositionConfig;
    Button buttonA = Button(BUTTON_A_PIN, true, 10);
    Button buttonB = Button(BUTTON_B_PIN, true, 10);
    Button buttonC = Button(BUTTON_C_PIN, true, 10);
    bool enabled = false;

    TaskHandle_t configuratorTask;
    void calibrate();
};

void runConfigurator(void *configurator);

#endif