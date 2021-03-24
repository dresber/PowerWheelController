#ifndef motor_H
#define motor_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define SPEED_RAMP_UP_INCREASE_DUTY_STEP 5

#define THROTTLE_PIN 2
#define SPEED_PIN 3
#define DIRECTION_PIN 4
#define RPWM_PIN 5
#define LPWM_PIN 6

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
enum ActiveMoving
{
  MOVING_OFF = 0,
  MOVING_RIGHT = 1,
  MOVING_LEFT = 2,
};

enum MovingDirection
{
    RIGHT = 0,
    LEFT = 1,
};

enum MotorSpeed
{
  MOTOR_MIN_SPEED = 100,
  MOTOR_SLOW_SPEED = 150,
  MOTOR_MEDIUM_SPEED = 180,
  MOTOR_NORMAL_SPEED = 210,
  MOTOR_FULL_SPEED = 255,
};

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //



// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void setup_motor_pins(void);
void process_motor_inputs(void);
void process_motor_outputs(void);

ActiveMoving get_actual_movement(void);
int get_actual_speed(void);
int get_actual_speed_setpoint(void);

#endif // #ifndef motor_H