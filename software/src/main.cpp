#include "solenoid_controller.hpp"

SolenoidController solenoidController;
TaskHandle_t solenoidControlTask;

void setup()
{
  solenoidController.initialize();
  solenoidController.enable();
  xTaskCreatePinnedToCore(startSolenoid, "SolenoidControlTask", 8192, &solenoidController, 1, &solenoidControlTask, 0);
}

void loop()
{
  int p = 5;
  int freq = 5;
  while (true)
  {
    delay(1000);
    if (freq >= 40)
    {
      p = -5;
    }
    else if (freq <= 5)
    {
      p = 5;
    }
    freq += p;
    solenoidController.setFrequency(freq);
  }
}
