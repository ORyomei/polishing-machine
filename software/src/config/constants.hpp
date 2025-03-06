#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//// CHANGEABLE ////

/// CONFIG の画面にするとRAWの値（センサーの生の値）が表示されます
/// ハンドルを回してヘッドを上下させ、2箇所における定規で読んだ値とそのときのRAWの値を
/// SENSOR_MIN, SENSOR_RAW_MIN, SENSOR_MAX, SENSOR_RAW_MAX に設定してください
/// （2点を取って直線を作っているだけなので、2箇所とればどこでもOKです。）
/// ここまで設定したら一度 M5Stack にプログラムを書き込んでください。（左下の "→" マークをクリック）

/// CONFIG の Lower position と Upper position とは別に、機械的に絶対に超えてほしくない値を
/// SENSOR_LOWER_LIMIT, SENSOR_UPPER_LIMIT に設定してください。
/// 設定した後、再度 M5Stack にプログラムを書き込んでください。（左下の "→" マークをクリック）

/// スイッチをOFFにしたときに、自動的に上に上がるポジションを STANDBY_POSITION に設定してください。

// MIN
#define SENSOR_MIN 10.0 // mm
#define SENSOR_RAW_MIN 650
// MAX
#define SENSOR_MAX 147.0 // mm
#define SENSOR_RAW_MAX 25250

#define SENSOR_LOWER_LIMIT 20.0  // mm
#define SENSOR_UPPER_LIMIT 140.0 // mm

#define STANDBY_POSITION 131.8

#define SOLENOID_DUTY 0.5

//// CHANGEABLE ABOVE ////

/////////////////////////////////
//// DO NOT CHANGE BELOW !!! ////
/////////////////////////////////

#define STEPPER_DIR_PIN 25
#define STEPPER_STEP_PIN 26
#define STEPPER_ENABLE_PIN 16

#define VIBRATOR_PIN 17

#define ADC_ALERT_PIN 5

#define BLDC_FWD_PIN 35
#define BLDC_REV_PIN 36

#define SOLENOID_DEFAULT_FREQUENCY 10

#define LOWER_POSITION 30.0
#define UPPER_POSITION 50.0

#endif