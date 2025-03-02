#include <Arduino.h>
#include "motor/motor_controller.hpp"
#include "motor/motor_state_controller.hpp"
#include "sensor/sensor.hpp"
#include "switch/switch.hpp"
#include "config/configurator.hpp"
#include "ui/ui.hpp"
#include "machine_state_controller.hpp"

Sensor sensor;
MotorController motorController = MotorController(sensor);
MotorStateController motorStateController = MotorStateController(&motorController);
Configurator configurator = Configurator(motorController, sensor);
MachineStateController machineStateConotroller = MachineStateController(motorStateController, sensor, configurator);
UI ui = UI(sensor, motorStateController, motorController, configurator, machineStateConotroller);

void setup()
{
  Serial.begin(115200);
  sensor.initialize();
  Serial.println("Sensor initialized");
  sensor.read();
  configurator.initialize();
  Serial.println("Configurator initialized");
  configurator.calibrateFromflash();
  motorStateController.initialize();
  machineStateConotroller.initialize();
  delay(1);
  // machineStateConotroller.start();
  ui.initialize();
  ui.start();
}

void loop()
{
  sensor.read();
  machineStateConotroller.update();
  delay(1);
}
