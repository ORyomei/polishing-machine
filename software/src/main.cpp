#include <Arduino.h>
#include "motor/motor_controller.hpp"
#include "motor/motor_state_controller.hpp"
#include "sensor/sensor.hpp"
#include "switch.hpp"
#include "config/configurator.hpp"
#include "ui.hpp"

Sensor sensor;
MotorSwitch motorSwitch = MotorSwitch();
MotorController motorController = MotorController(sensor);
MotorStateController motorStateController = MotorStateController(&motorController);
Configurator configurator = Configurator(motorController, sensor);
UI ui = UI(sensor, motorStateController, configurator);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");
  sensor.initialize();
  Serial.println("Sensor initialized");
  motorSwitch.initialize();
  Serial.println("Switch initialized");
  sensor.read();
  configurator.initialize();
  Serial.println("Configurator initialized");
  configurator.calibrateFromflash();
  configurator.start();
  motorStateController.initialize();
  ui.initialize();
  ui.start();
}

void loop()
{
  motorSwitch.read();
  if (motorSwitch.changed())
  {
    motorStateController.setState(motorSwitch.getState());
  }
  sensor.read();
  if (!sensor.isInRange())
  {
    if (motorStateController.motorRunning())
    {
      motorStateController.off();
    }
  }
}
