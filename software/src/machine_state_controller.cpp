#include "machine_state_controller.hpp"

MachineStateController::MachineStateController(MotorStateController &motorStateController, Vibrator &vibrator, Sensor &sensor, Configurator &configurator)
    : motorStateController(motorStateController), vibrator(vibrator), sensor(sensor), configurator(configurator)
{
    state = MachineState::OFF;
}

void MachineStateController::initialize()
{
    motorSwitch.initialize();
}

void MachineStateController::update()
{
    buttonA.read();
    motorSwitch.read();
    MachineState nextState = state;
    switch (state)
    {
    case MachineState::OFF:
        if (motorSwitch.getState() == MotorSwitchState::EMERGENCY)
        {
            nextState = MachineState::EMERGENCY;
        }
        else if (!sensor.isInRange())
        {
            nextState = MachineState::OUT_OF_RANGE;
        }
        else if (buttonA.wasReleased())
        {
            configurator.enable();
            nextState = MachineState::CONFIGURATING;
        }
        else if (motorSwitch.changed() && motorSwitch.getState() == MotorSwitchState::ON)
        {
            motorStateController.setState(MotorSwitchState::ON);
            vibrator.on();
            nextState = MachineState::RUNNING;
        }
        break;
    case MachineState::CONFIGURATING:
        if (motorSwitch.getState() == MotorSwitchState::EMERGENCY)
        {
            configurator.disable();
            nextState = MachineState::EMERGENCY;
        }
        else if (buttonA.wasReleasefor(3000))
        {
            configurator.saveAndDisable();
            nextState = sensor.isInRange() ? MachineState::OFF : MachineState::OUT_OF_RANGE;
        }
        else if (buttonA.wasReleased())
        {
            configurator.disable();
            nextState = sensor.isInRange() ? MachineState::OFF : MachineState::OUT_OF_RANGE;
        }
        break;
    case MachineState::RUNNING:
        if (!motorStateController.motorRunning())
        {
            nextState = MachineState::OFF;
        }
        if (motorSwitch.getState() == MotorSwitchState::EMERGENCY)
        {
            motorStateController.setState(MotorSwitchState::EMERGENCY);
            vibrator.off();
            nextState = MachineState::EMERGENCY;
        }
        else if (!sensor.isInRange())
        {
            motorStateController.setState(MotorSwitchState::EMERGENCY);
            vibrator.off();
            nextState = MachineState::OUT_OF_RANGE;
        }
        else if (motorSwitch.changed() && motorSwitch.getState() == MotorSwitchState::OFF)
        {
            motorStateController.setState(MotorSwitchState::OFF);
            vibrator.off();
        }
        break;
    case MachineState::EMERGENCY:
        if (motorSwitch.changed() && motorSwitch.getState() == MotorSwitchState::OFF)
        {
            nextState = sensor.isInRange() ? MachineState::OFF : MachineState::OUT_OF_RANGE;
        }
        break;
    case MachineState::OUT_OF_RANGE:
        if (motorSwitch.getState() == MotorSwitchState::EMERGENCY)
        {
            nextState = MachineState::EMERGENCY;
        }
        else if (sensor.isInRange() && motorSwitch.getState() == MotorSwitchState::OFF)
        {
            nextState = MachineState::OFF;
        }
        else if (buttonA.wasReleased() && motorSwitch.getState() == MotorSwitchState::OFF)
        {
            configurator.enable();
            nextState = MachineState::CONFIGURATING;
        }
        break;
    default:
        break;
    }
    if (nextState != state)
    {
        state = nextState;
        Serial.printf("MachineState: %s\n", MachineStateToString(state));
    }
}

void MachineStateController::run()
{
    while (true)
    {
        update();
        delay(MACHINE_STATE_CONTROLLER_CYCLE_TIME);
    }
}

void MachineStateController::start()
{
    xTaskCreatePinnedToCore(runMachineStateController, "MachineStateController", 32768, this, 2, &taskHandle, 0);
}

void runMachineStateController(void *machineStateController)
{
    ((MachineStateController *)machineStateController)->run();
}

const char *MachineStateToString(MachineState state)
{
    switch (state)
    {
    case MachineState::OFF:
        return "OFF";
    case MachineState::CONFIGURATING:
        return "CONFIGURATING";
    case MachineState::RUNNING:
        return "RUNNING";
    case MachineState::EMERGENCY:
        return "EMERGENCY";
    case MachineState::OUT_OF_RANGE:
        return "OUT_OF_RANGE";
    }
    return "UNKNOWN";
}