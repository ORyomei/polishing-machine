#include <Arduino.h>
#include <AccelStepper.h>

#define STEPPER_DIR_PIN 26
#define STEPPER_STEP_PIN 23

AccelStepper stepper = AccelStepper(AccelStepper::FULL2WIRE, STEPPER_STEP_PIN, STEPPER_DIR_PIN); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{
  Serial.begin(115200);
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(6000);
  stepper.moveTo(25000);
}

void loop()
{
  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run();
}
