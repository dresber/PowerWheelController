// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "drive_control.h"

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

static int16_t _forward_speed_level = START_LEVEL_FORWARD;
static int16_t _backward_speed_level = START_LEVEL_BACKWARD;

static int16_t _speed_levels[NR_OF_SPEED_LEVEL] = {SPEED_LEVEL_1, SPEED_LEVEL_2, SPEED_LEVEL_3, SPEED_LEVEL_4};

static DriveDirection _actual_direction = DIR_OFF;


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
static void _increase_speed_level(void);
static void _reduce_speed_level(void);


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_drive_control(void)
{
    pinMode(DIRECITON_BACKWARD_INPUT, INPUT_PULLUP);
    pinMode(DIRECTION_FORWARD_INPUT, INPUT_PULLUP);    
    pinMode(SPEED_PLUS_INPUT, INPUT_PULLUP);
    pinMode(SPEED_MINUS_INPUT, INPUT_PULLUP);    
}

/**
 * 
 */
void process_drive_control(void)
{
    static bool prev_speed_plus_btn_state = digitalRead(SPEED_PLUS_INPUT);
    static bool prev_speed_minus_btn_state = digitalRead(SPEED_MINUS_INPUT);

    if (_remote_controlled == false)
    {
        if(digitalRead(DIRECTION_FORWARD_INPUT) == LOW)
        {
            if (_actual_direction != DIR_FORWARD)
            {
                _forward_speed_level = START_LEVEL_FORWARD;
            }
            _actual_direction = DIR_FORWARD;
        }
        else if (digitalRead(DIRECITON_BACKWARD_INPUT) == LOW)
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
    if((_actual_direction != direction) && (_actual_direction != DIR_OFF))
    {
        _actual_direction = DIR_OFF;
    }
    else
    {
        _actual_direction = direction;
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
