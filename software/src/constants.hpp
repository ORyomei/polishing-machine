#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//////////////////////////
/// Stepper Motor Pins ///
//////////////////////////

#define STEPPER_DIR_PIN 26
#define STEPPER_STEP_PIN 23
#define STEPPER_ENABLE_PIN 25

/////////////////////
/// Solenoid Pins ///
/////////////////////
#define SOLENOID_PIN 12

////////////////
/// Adc Pins ///
////////////////
#define ADC_ALERT_PIN 4

///////////////////
/// Button Pins ///
///////////////////
#define BUTTON_A_PIN 13
#define BUTTON_B_PIN 26
#define BUTTON_C_PIN 25

#define SOLENOID_DUTY 0.5
#define SOLENOID_DEFAULT_FREQUENCY 10

#define LOWER_POSITION 60.0
#define UPPER_POSITION 80.0
#define STANDBY_POSITION 110.0

#define FWD_PIN 18
#define REV_PIN 19

#endif