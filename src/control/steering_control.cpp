// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "steering_control.h"

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
static bool _remote_enabled = false;

static SteeringDirection _act_steering = STEER_STRAIGHT;

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_steering_control(void)
{
    pinMode(STEERING_LEFT_OUTPUT, OUTPUT);
    pinMode(STEERING_RIGHT_OUTPUT, OUTPUT);
}

/**
 * 
 */
void process_steering_control(void)
{
    if (_remote_enabled == true)
    {
#ifdef SAFETY
        if (get_safety_state() != SAFETY_OK)
        {
            _act_steering = STEER_STRAIGHT;
        }
#endif // #ifdef SAFETY
    }
    else
    {
        _act_steering = STEER_STRAIGHT;
    }

    switch (_act_steering)
    {
        case STEER_STRAIGHT:
            digitalWrite(STEERING_LEFT_OUTPUT, LOW);
            digitalWrite(STEERING_RIGHT_OUTPUT, LOW);
            break;
        case STEER_LEFT:
            digitalWrite(STEERING_RIGHT_OUTPUT, LOW);
            digitalWrite(STEERING_LEFT_OUTPUT, HIGH);
            break;
        case STEER_RIGHT:
            digitalWrite(STEERING_LEFT_OUTPUT, LOW);
            digitalWrite(STEERING_RIGHT_OUTPUT, HIGH);
            break;
    }
}

/**
 * 
 */
SteeringDirection get_steering_direction(void)
{
    return(_act_steering);
}


/**
 * 
 */
void set_steering_direction(SteeringDirection direction)
{
    _act_steering = direction;
}


/**
 * 
 */
void set_remote_state(bool state)
{
    _remote_enabled = state;
}