#ifndef _MACHINE_STATE_CONTROLLER_H_
#define _MACHINE_STATE_CONTROLLER_H_

#include "motor/motor_state_controller.hpp"
#include "sensor/sensor.hpp"
#include "config/configurator.hpp"
#include "switch/switch.hpp"
#include "vibrator/vibrator.hpp"
#include <utility/Button.h>
#include <utility/Config.h>

#define MACHINE_STATE_CONTROLLER_CYCLE_TIME 10

enum class MachineState
{
    OFF,
    CONFIGURATING,
    RUNNING,
    EMERGENCY,
    OUT_OF_RANGE,
};

class MachineStateController
{
public:
    MachineStateController(MotorStateController &motorStateController, Vibrator &vibrator, Sensor &sensor, Configurator &configurator);
    void initialize();
    void update();
    void run();
    void start();
    MachineState getState() { return state; }

private:
    MotorStateController &motorStateController;
    Vibrator &vibrator;
    Sensor &sensor;
    Configurator &configurator;
    MotorSwitch motorSwitch = MotorSwitch();
    Button buttonA = Button(BUTTON_A_PIN, true, 50);
    MachineState state;
    TaskHandle_t taskHandle;
};

void runMachineStateController(void *machineStateController);

const char *MachineStateToString(MachineState state);

#endif