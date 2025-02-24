#ifndef _MOTOR_STATE_H_
#define _MOTOR_STATE_H_

enum class MotorState
{
    OFF,
    ON,
    MOVE_TO_STANDBY
};

enum class MotorSwitchState
{
    OFF,
    ON,
    EMERGENCY
};

#endif