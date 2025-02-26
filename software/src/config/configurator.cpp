#include "configurator.hpp"

void UpperLowerPositionConfig::loadFromConstants()
{
    upperPosition = UPPER_POSITION;
    lowerPosition = LOWER_POSITION;
}

bool UpperLowerPositionConfig::loadFromJsonStr(const char *jsonStr)
{

    StaticJsonDocument<100> json;
    DeserializationError error = deserializeJson(json, jsonStr);

    bool ok = !bool(error);
    ok &= json.containsKey("upperPosition");
    ok &= json.containsKey("lowerPosition");
    if (!ok)
    {
        // メンバーが足りなかったときは何もせず False を返す
        return false;
    }
    upperPosition = json["upperPosition"];
    lowerPosition = json["lowerPosition"];
    return true;
}

const char *UpperLowerPositionConfig::toJsonStr()
{
    StaticJsonDocument<100> json;
    json["upperPosition"] = upperPosition;
    json["lowerPosition"] = lowerPosition;
    char *jsonStr = new char[100];
    serializeJson(json, jsonStr, 100);
    return jsonStr;
}

void Configurator::initialize()
{
    flash.initialize();
    // TODO initialize 失敗時の処理
}

void Configurator::enable()
{
    enabled = true;
}

void Configurator::disable()
{
    enabled = false;
    flash.write(UPPER_LOWER_POSITION_FILE_NAME, upperLowerPositionConfig.toJsonStr());
}

void Configurator::calibrate()
{
    motorController.setUpperPosition(upperLowerPositionConfig.upperPosition);
    motorController.setLowerPosition(upperLowerPositionConfig.lowerPosition);
}

void Configurator::loadUpperLowerPositionFromFlash()
{
    const char *jsonStr = flash.read(UPPER_LOWER_POSITION_FILE_NAME);
    if (!upperLowerPositionConfig.loadFromJsonStr(jsonStr))
    {
        // False のときは Constants から読み込む。
        upperLowerPositionConfig.loadFromConstants();
    }
}

void Configurator::calibrateFromflash()
{
    loadUpperLowerPositionFromFlash();
    calibrate();
}

void Configurator::setCurrentPositionUpper()
{
    upperLowerPositionConfig.upperPosition = sensor.convertedValue();
    motorController.setUpperPosition(upperLowerPositionConfig.upperPosition);
    Serial.printf("Upper Position: %f\n", upperLowerPositionConfig.upperPosition);
}

void Configurator::setCurrentPositionLower()
{
    upperLowerPositionConfig.lowerPosition = sensor.convertedValue();
    motorController.setLowerPosition(upperLowerPositionConfig.lowerPosition);
    Serial.printf("Lower Position: %f\n", upperLowerPositionConfig.lowerPosition);
}

void Configurator::run()
{
    while (true)
    {
        buttonA.read();
        buttonB.read();
        buttonC.read();
        if (buttonA.wasPressed())
        {
            if (!enabled)
            {
                enable();
            }
            else
            {
                disable();
            }
        }
        else if (buttonB.wasPressed())
        {
            if (enabled)
            {
                setCurrentPositionUpper();
            }
        }
        else if (buttonC.wasPressed())
        {
            if (enabled)
            {
                setCurrentPositionLower();
            }
        }
        delay(10);
    }
}

void Configurator::start()
{
    xTaskCreatePinnedToCore(runConfigurator, "Configurator", 10000, this, 2, &configuratorTask, 0);
}

void runConfigurator(void *configurator)
{
    Configurator *c;
    c = (Configurator *)configurator;
    c->run();
}