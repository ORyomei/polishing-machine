#include "configurator.hpp"

Configurator::Configurator(MotorController &motorController, Sensor &sensor) : motorController(motorController), sensor(sensor) {}

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

void UpperLowerPositionConfig::copyFrom(UpperLowerPositionConfig &config)
{
    upperPosition = config.upperPosition;
    lowerPosition = config.lowerPosition;
}

void Configurator::initialize()
{
    flash.initialize();
    // TODO initialize 失敗時の処理

    xTaskCreatePinnedToCore(runConfigurator, "Configurator", 4096, this, 2, &taskHandle, 0);
    vTaskDelete(taskHandle);
}

void Configurator::enable()
{
    Serial.println("Configurator Enabled");
    upperLowerPositionConfigTemp.copyFrom(upperLowerPositionConfig);
    start();
    _enabled = true;
}

void Configurator::disable()
{
    Serial.println("Configurator Disabled");
    motorController.setUpperPosition(upperLowerPositionConfig.upperPosition);
    motorController.setLowerPosition(upperLowerPositionConfig.lowerPosition);
    stop();
    _enabled = false;
}

void Configurator::saveAndDisable()
{
    Serial.println("Configurator Save and Disable");
    upperLowerPositionConfig.copyFrom(upperLowerPositionConfigTemp);
    flash.write(UPPER_LOWER_POSITION_FILE_NAME, upperLowerPositionConfig.toJsonStr());
    _enabled = false;
}

bool Configurator::enabled()
{
    return _enabled;
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
    upperLowerPositionConfigTemp.upperPosition = sensor.convertedValue();
    motorController.setUpperPosition(upperLowerPositionConfigTemp.upperPosition);
    Serial.printf("Upper Position: %f\n", upperLowerPositionConfig.upperPosition);
}

void Configurator::setCurrentPositionLower()
{
    upperLowerPositionConfigTemp.lowerPosition = sensor.convertedValue();
    motorController.setLowerPosition(upperLowerPositionConfigTemp.lowerPosition);
    Serial.printf("Lower Position: %f\n", upperLowerPositionConfig.lowerPosition);
}

void Configurator::cycle()
{
    buttonB.read();
    buttonC.read();
    if (buttonB.wasPressed())
    {
        if (enabled())
        {
            setCurrentPositionUpper();
        }
    }
    else if (buttonC.wasPressed())
    {
        if (enabled())
        {
            setCurrentPositionLower();
        }
    }
}

void Configurator::run()
{
    while (true)
    {
        cycle();
        delay(CONFIGURATOR_CYCLE_TIME);
    }
}

void Configurator::start()
{
    if (eTaskGetState(taskHandle) != eRunning)
    {
        xTaskCreatePinnedToCore(runConfigurator, "Configurator", 4096, this, 2, &taskHandle, 0);
    }
}

void Configurator::stop()
{
    if (eTaskGetState(taskHandle) == eRunning)
    {
        vTaskDelete(taskHandle);
    }
}

void runConfigurator(void *configurator)
{
    Configurator *c;
    c = (Configurator *)configurator;
    c->run();
}