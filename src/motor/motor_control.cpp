// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "motor/motor_control.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static int actual_speed = 0;
static int actual_speed_setpoint = MOTOR_MIN_SPEED;

static ActiveMoving actual_movement = MOVING_OFF;
static MovingDirection actual_direction = RIGHT;

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
static void motor_ramp_up(int pin_nr, int speed_setpoint);

// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
static void motor_ramp_up(int pin_nr, int speed_setpoint)
{
    if (actual_speed < speed_setpoint)
    {
        if ((actual_speed + SPEED_RAMP_UP_INCREASE_DUTY_STEP) < speed_setpoint)
        {
        actual_speed += SPEED_RAMP_UP_INCREASE_DUTY_STEP;
        }
        else
        {
        actual_speed = speed_setpoint;
        }
        
        analogWrite(pin_nr, actual_speed);
    }
    else if (actual_speed > speed_setpoint)
    {
        if ((actual_speed - SPEED_RAMP_UP_INCREASE_DUTY_STEP) > speed_setpoint)
        {
        actual_speed -= SPEED_RAMP_UP_INCREASE_DUTY_STEP;
        }
        else
        {
        actual_speed = speed_setpoint;
        }
        
        analogWrite(pin_nr, actual_speed);
    }
}

/**
 *
 */
void setup_motor_pins(void)
{
    pinMode(RPWM_PIN, OUTPUT);
    pinMode(LPWM_PIN, OUTPUT);

    
    pinMode(THROTTLE_PIN, INPUT);
    pinMode(SPEED_PIN, INPUT);
    pinMode(DIRECTION_PIN, INPUT);

    digitalWrite(THROTTLE_PIN, HIGH);
    digitalWrite(SPEED_PIN, HIGH);
    digitalWrite(DIRECTION_PIN, HIGH);
}

/**
 *
 */
void process_motor_inputs(void)
{
    static bool prev_speed_btn_state = digitalRead(SPEED_PIN);
    static bool prev_direction_btn_state = digitalRead(DIRECTION_PIN);
    
    if (digitalRead(DIRECTION_PIN) != prev_direction_btn_state)
    {
        prev_direction_btn_state = digitalRead(DIRECTION_PIN);

        if (!digitalRead(DIRECTION_PIN) && digitalRead(THROTTLE_PIN))
        {
            if (actual_direction == RIGHT)
            {
                actual_direction = LEFT;
            }
            else
            {
                actual_direction = RIGHT;
            }
        }
    }

    if (digitalRead(SPEED_PIN) != prev_speed_btn_state)
    {
        prev_speed_btn_state = digitalRead(SPEED_PIN);

        if(!digitalRead(SPEED_PIN))
        {
            switch (actual_speed_setpoint)
            {
                case MOTOR_MIN_SPEED:
                    actual_speed_setpoint = MOTOR_SLOW_SPEED;
                    break;
                case MOTOR_SLOW_SPEED:
                    actual_speed_setpoint = MOTOR_MEDIUM_SPEED;
                    break;
                case MOTOR_MEDIUM_SPEED:
                    actual_speed_setpoint = MOTOR_NORMAL_SPEED;
                    break;
                case MOTOR_NORMAL_SPEED:
                    actual_speed_setpoint = MOTOR_FULL_SPEED;
                    break;
                case MOTOR_FULL_SPEED:
                    actual_speed_setpoint = MOTOR_MIN_SPEED;
                    break;
                default:
                    actual_speed_setpoint = MOTOR_MIN_SPEED;
                    break;
            }
        }
    }

    if (digitalRead(THROTTLE_PIN))
    {
        actual_speed = 0;
        actual_movement = MOVING_OFF;
    }
    else
    {
        if (actual_direction == LEFT)
        {
            actual_movement = MOVING_LEFT;
        }
        else
        {
            actual_movement = MOVING_RIGHT;
        }
    }
}


/**
 *
 */
void process_motor_outputs(void)
{
  switch (actual_movement)
  {
    case MOVING_OFF:
      analogWrite(RPWM_PIN, 0);
      analogWrite(LPWM_PIN, 0);
      break;
    case MOVING_RIGHT:
      analogWrite(LPWM_PIN, 0);
      motor_ramp_up(RPWM_PIN, actual_speed_setpoint);
      break;
    case MOVING_LEFT:
      analogWrite(RPWM_PIN, 0);
      motor_ramp_up(LPWM_PIN, actual_speed_setpoint);
      break;
  }
}


/**
 *
 */
int get_actual_speed(void)
{
    return actual_speed;
}


/**
 *
 */
int get_actual_speed_setpoint(void)
{
    return actual_speed_setpoint;
}


/**
 *
 */
ActiveMoving get_actual_movement(void)
{
    return actual_movement;
}