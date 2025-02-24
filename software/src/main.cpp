#include <Arduino.h>
#include "motor/motor_controller.hpp"
#include "motor/motor_state_controller.hpp"
#include "sensor/sensor.hpp"
#include "switch.hpp"

Sensor sensor;
MotorSwitch motorSwitch = MotorSwitch(FWD_PIN, REV_PIN);
MotorController motorController = MotorController(sensor);
MotorStateController motorStateController = MotorStateController(&motorController);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");
  sensor.initialize();
  motorSwitch.initialize();
  sensor.read();
  Serial.println("Sensor initialized");
  motorStateController.initialize();
}

void loop()
{
  motorSwitch.read();
  if (motorSwitch.changed())
  {
    motorStateController.setState(motorSwitch.getState());
  }
  sensor.read();
  // Serial.printf("Raw: %d, Converted: %f\n", sensor.getRawValue(), sensor.convertedValue());
  if (!sensor.isInRange())
  {
    motorController.off();
  }
}
