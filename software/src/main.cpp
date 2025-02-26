#include <Arduino.h>
#include "motor/motor_controller.hpp"
#include "motor/motor_state_controller.hpp"
#include "sensor/sensor.hpp"
#include "switch.hpp"
#include "config/configurator.hpp"

Sensor sensor;
MotorSwitch motorSwitch = MotorSwitch();
MotorController motorController = MotorController(sensor);
MotorStateController motorStateController = MotorStateController(&motorController);
Configurator configurator = Configurator(motorController, sensor);

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
  configurator.calibrateFromflash();
  configurator.start();
  motorStateController.initialize();
}

void loop()
{
  motorSwitch.read();
  // Serial.printf("Switched: %d, State: %d\n", motorSwitch.changed(), motorSwitch.getState());
  if (motorSwitch.changed())
  {
    motorStateController.setState(motorSwitch.getState());
  }
  sensor.read();
  // Serial.printf("Raw: %d, Converted: %f\n", sensor.getRawValue(), sensor.convertedValue());
  if (!sensor.isInRange())
  {
    if (motorStateController.motorRunning())
    {
      motorStateController.off();
    }
  }
}
