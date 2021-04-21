// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "drive_control.h"

#if defined(DISTANCE_SENSOR_FRONT_1) || defined(DISTANCE_SENSOR_FRONT_2) || defined(DISTANCE_SENSOR_BACK)
#include "sensors/distance.h"
#endif // #ifdef DISTANCE_SENSOR_FRONT_1 || DISTANCE_SENSOR_FRONT_2 || DISTANCE_SENSOR_BACK

#ifdef SAFETY
#include "safety/safety.h"
#endif // #ifdef SAFETY

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static bool _remote_controlled = false;
static bool _collision_warning_active = false;

static int16_t _forward_speed_level = START_LEVEL_FORWARD;
static int16_t _backward_speed_level = START_LEVEL_BACKWARD;
static int16_t _act_speed = 0;
static int16_t _last_throttle_speed_set = 0;

static int16_t _speed_levels[NR_OF_SPEED_LEVEL] = {SPEED_LEVEL_1, SPEED_LEVEL_2, SPEED_LEVEL_3, SPEED_LEVEL_4};

static int64_t _last_throttle_active = 0;

static DriveDirection _actual_direction = DIR_OFF;

static MovementState _actual_movement = MOV_STOPPED;

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
static void _increase_speed_level(void);
static void _reduce_speed_level(void);
static void _process_direction_switch(void);
static void _process_speed_btns(void);
static void _process_throttle(void);
static void _process_motor(void);
static void _ramp_motor_pwm(void);
static void _motor_fast_stop(void);
static void _motor_delayed_stop(void);

static bool _check_if_way_not_blocked(void);
static int16_t _calc_safety_distance(void);

// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_drive_control(void)
{
    pinMode(DIRECTION_BACKWARD_INPUT, INPUT_PULLUP);
    pinMode(DIRECTION_FORWARD_INPUT, INPUT_PULLUP);    
    pinMode(THROTTLE_INPUT, INPUT_PULLUP);    
    pinMode(SPEED_PLUS_INPUT, INPUT_PULLUP);
    pinMode(SPEED_MINUS_INPUT, INPUT_PULLUP);

    pinMode(MOTOR_FORWARD_PWM, OUTPUT);    
    pinMode(MOTOR_BACKWARD_PWM, OUTPUT);    
    pinMode(MOTOR_BREAK_OUTPUT, OUTPUT);
}

/**
 * 
 */
void process_drive_control(void)
{
    if (_remote_controlled == false)
    {
        _process_direction_switch();
        _process_speed_btns();
        _process_throttle();
    }

    _process_motor();
}

/**
 * 
 */
DriveDirection get_moving_direction(void)
{
    return (_actual_direction);
}

/**
 * 
 */
int16_t get_actual_speed_level(void)
{
    if (_actual_direction == DIR_FORWARD)
    {
        return (_forward_speed_level);
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
        return(_backward_speed_level);
    }
    else
    {
        return (0);
    }
}

/**
 * 
 */
int16_t get_actual_speed_pwm_value(void)
{
    if (_actual_direction == DIR_FORWARD)
    {
        return (_speed_levels[_forward_speed_level]);
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
        return (_speed_levels[_backward_speed_level]);
    }
    else
    {
        return (0);
    }
}

/**
 * 
 */
void set_remote_control_enabled(bool enabled)
{
    _remote_controlled = enabled;
}

/**
 * 
 */
void set_moving_direction(DriveDirection direction)
{
    if (_remote_controlled == true)
    {
        if((_actual_direction != direction) && (_actual_direction != DIR_OFF))
        {
            _actual_direction = DIR_OFF;
        }
        else
        {
            _actual_direction = direction;
        }
    }
}

/**
 * 
 */
void increase_speed_level(void)
{
    _increase_speed_level();
}


/**
 * 
 */
void reduce_speed_level(void)
{
    _reduce_speed_level();
}


/**
 * 
 */
void set_throttle(bool throttle_state)
{
    if (_remote_controlled == true)
    {
        if (throttle_state)
        {
            _actual_movement = MOV_ACTIVE;
        }
        else
        {
            _actual_movement = MOV_STOPPED;
        }
    }
}


/**
 * 
 */
bool get_active_collision_warning(void)
{
    return(_collision_warning_active);
}


static void _increase_speed_level(void)
{
    if(_actual_direction == DIR_FORWARD)
    {
        if(_forward_speed_level < MAX_LEVEL_FORWARD)
        {
            _forward_speed_level++;
        }
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
        if(_backward_speed_level < MAX_LEVEL_BACKWARD)
        {
            _backward_speed_level++;
        }
    }
}

static void _reduce_speed_level(void)
{
    if(_actual_direction == DIR_FORWARD)
    {
        if(_forward_speed_level > 1)
        {
            _forward_speed_level--;
        }
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
        if(_backward_speed_level > 1)
        {
            _backward_speed_level--;
        }
    }
}

static void _process_direction_switch(void)
{
    if (_act_speed == 0)
    {
        if(digitalRead(DIRECTION_FORWARD_INPUT) == LOW)
        {
            if (_actual_direction != DIR_FORWARD)
            {
                _forward_speed_level = START_LEVEL_FORWARD;
            }
            _actual_direction = DIR_FORWARD;
            
        }
        else if (digitalRead(DIRECTION_BACKWARD_INPUT) == LOW)
        {
            if (_actual_direction != DIR_BACKWARD)
            {
                _backward_speed_level = START_LEVEL_BACKWARD;
            }
            _actual_direction = DIR_BACKWARD;
        }
        else
        {
            _actual_direction = DIR_OFF;
        }
    }
}


static void _process_speed_btns(void)
{
    static bool prev_speed_plus_btn_state = digitalRead(SPEED_PLUS_INPUT);
    static bool prev_speed_minus_btn_state = digitalRead(SPEED_MINUS_INPUT);

    if (prev_speed_plus_btn_state != digitalRead(SPEED_PLUS_INPUT))
    {
        prev_speed_plus_btn_state = digitalRead(SPEED_PLUS_INPUT);

        if (digitalRead(SPEED_PLUS_INPUT) == LOW)
        {
            _increase_speed_level();
        }
    }

    if (prev_speed_minus_btn_state != digitalRead(SPEED_MINUS_INPUT))
    {
        prev_speed_minus_btn_state = digitalRead(SPEED_MINUS_INPUT);

        if (digitalRead(SPEED_MINUS_INPUT) == LOW)
        {
            _reduce_speed_level();
        }
    } 
}


static void _process_throttle(void)
{
    if(digitalRead(THROTTLE_INPUT) == LOW)
    {
        _actual_movement = MOV_ACTIVE;
    }
    else
    {
        _actual_movement = MOV_STOPPED;
    }
}


static void _process_motor(void)
{
    if (_actual_movement == MOV_ACTIVE)
    {
#ifdef SAFETY
        if (get_safety_state() == SAFETY_OK)
        {
#endif // #ifdef SAFETY
            if (_check_if_way_not_blocked())
            {
                _collision_warning_active = false;

                _last_throttle_speed_set = millis();

                digitalWrite(MOTOR_BREAK_OUTPUT, LOW);

                _ramp_motor_pwm();

            }
            else
            {
                _collision_warning_active = true;
                _motor_delayed_stop();
            }
#ifdef SAFETY
        }
        else
        {
            _motor_fast_stop();
        }
#endif // #ifdef SAFETY
    }
    else
    {
        _motor_delayed_stop();
    }
}


static bool _check_if_way_not_blocked(void)
{
    uint16_t safe_distance = (uint16_t)_calc_safety_distance();

    if (_actual_direction == DIR_FORWARD)
    {
#ifdef DISTANCE_SENSOR_FRONT_1
        if (get_front_sensor_1_distance_in_cm() < safe_distance)
        {
            return (false);
        }
#endif // #ifdef DISTANCE_SENSOR_FRONT_1

#ifdef DISTANCE_SENSOR_FRONT_2
        if (get_front_sensor_2_distance_in_cm() < safe_distance)
        {
            return (false);
        }
#endif // #ifdef DISTANCE_SENSOR_FRONT_1
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
#ifdef DISTANCE_SENSOR_BACK
        if (get_back_sensor_distance_in_cm() < safe_distance)
        {
            return (false);
        }
#endif // #ifdef DISTANCE_SENSOR_BACK	
    }

    return (true);
}


static int16_t _calc_safety_distance(void)
{
    int16_t minimum_distance = MIN_DIST_AT_MAX_SPEED;

    int16_t k_100 = (MIN_DIST_AT_MAX_SPEED - MIN_DIST_AT_MIN_SPEED) * 100 / (SPEED_LEVEL_4 - SPEED_LEVEL_1);

    minimum_distance = k_100 * _act_speed / 100 + MIN_DIST_AT_MIN_SPEED - ((k_100 * SPEED_LEVEL_1) / 100);

    if (minimum_distance < MIN_DIST_AT_MIN_SPEED)
    {
        minimum_distance = MIN_DIST_AT_MIN_SPEED;
    }

    return (minimum_distance);
}


static void _motor_fast_stop(void)
{
    _act_speed = 0;

    analogWrite(MOTOR_FORWARD_PWM, 0);
    analogWrite(MOTOR_BACKWARD_PWM, 0);

    digitalWrite(MOTOR_BREAK_OUTPUT, HIGH);
}


static void _motor_delayed_stop(void)
{
    static int64_t last_speed_reduction = 0;

    if (_act_speed > SPEED_LEVEL_1)
    {
        if (millis() > (last_speed_reduction + BRAKE_MILLIS_FOR_10_DUTY_CYCLE))
        {
            _act_speed -= 10;
            last_speed_reduction = millis();
        }
    }
    else
    {
        _act_speed = 0;
    }

    if (_actual_direction == DIR_FORWARD)
    {
        analogWrite(MOTOR_FORWARD_PWM, _act_speed);
    }
    else if (_actual_direction == DIR_BACKWARD)
    {
        analogWrite(MOTOR_BACKWARD_PWM, _act_speed);
    }
    else
    {
        analogWrite(MOTOR_BACKWARD_PWM, 0);
        analogWrite(MOTOR_FORWARD_PWM, 0);
    }

    if (millis() > ((BRAKE_DELAY_MILLIS_PER_DUTY_CYCLE * _last_throttle_speed_set) + _last_throttle_active))
    {
        digitalWrite(MOTOR_BREAK_OUTPUT, HIGH);
    }
}


static void _ramp_motor_pwm(void)
{
    static int64_t last_increase = 0;
    int16_t pwm_pin = 0;
    int16_t *_speed_level;

    if (_actual_direction == DIR_FORWARD)
    {
        pwm_pin = MOTOR_FORWARD_PWM;
        _speed_level = &_forward_speed_level;
    }
    else
    {
        pwm_pin = MOTOR_BACKWARD_PWM;
        _speed_level = &_backward_speed_level;
    }

    if (_act_speed < *_speed_level)
    {
        if(millis() > (last_increase + ACCELARATION_MILLIS_FOR_5_DUTY_CYCLE))
        {
            last_increase = millis();

            if ((_act_speed + ACCELARATION_DUTY_CYCLE_STEPS) < *_speed_level)
            {
                _act_speed += ACCELARATION_DUTY_CYCLE_STEPS;
            }
            else
            {
                _act_speed = *_speed_level;
            }
        }
    }
    else if (_act_speed > *_speed_level)
    {
        if(millis() > (last_increase + ACCELARATION_MILLIS_FOR_5_DUTY_CYCLE))
        {
            last_increase = millis();

            if ((_act_speed - ACCELARATION_DUTY_CYCLE_STEPS) > *_speed_level)
            {
                _act_speed -= ACCELARATION_DUTY_CYCLE_STEPS;
            }
            else
            {
                _act_speed = *_speed_level;
            }        
        }
    }
    
    _last_throttle_speed_set = _act_speed;

    analogWrite(pwm_pin, _act_speed);
}