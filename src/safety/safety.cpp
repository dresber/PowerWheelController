 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "safety.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static RemoteState remote_state = OFF;
static SafetyState safety_state = OK;
static int64_t last_wdg_trig_millis = 0;


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
static void _disable_safety_pins(void);
static void _enable_safety_pins(void);
static bool _check_wdg_trig_received_in_time(void);


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_safety(void)
{
    pinMode(MOTOR_ENABLE_LEFT, OUTPUT);
    pinMode(MOTOR_ENABLE_RIGHT, OUTPUT);
}


/**
 * 
 */
void process_safety(void)
{
    switch (remote_state)
    {
    case OFF:
        /* code */
        break;

    case MONITOR:
    case CONTROL:
        if (safety_state != EMERGENCY_STOP)
        {
            if (_check_wdg_trig_received_in_time())
            {

            }
            else
            {
                safety_state = EMERGENCY_STOP;
            }
        }
        break;    
    default:
        break;
    }


    switch (safety_state)
    {
    case OK:
        _enable_safety_pins();
        break;
    
    case HALT:
    case EMERGENCY_STOP:
        _disable_safety_pins();
        break;

    default:
        break;
    }

}


/**
 * 
 */
void set_remote_state(RemoteState state)
{
    remote_state = state;
}


/**
 * 
 */
RemoteState get_remote_state(void)
{
    return(remote_state);
}


/**
 * 
 */
void trigger_remote_wdg(void)
{
    last_wdg_trig_millis = millis();
}


/**
 * 
 */
void set_emergency_stop(void)
{
    safety_state = EMERGENCY_STOP;
    _disable_safety_pins();
}


/**
 * 
 */
void reset_emergency_stop(void)
{
    safety_state = OK;
}

/**
 * 
 */
SafetyState get_safety_state(void)
{
    return(safety_state);
}


// ------------------------------------------------ //
//           static function definitions
// ------------------------------------------------ //
static bool _check_wdg_trig_received_in_time(void)
{
    if (millis() - last_wdg_trig_millis > WDG_TRIG_TIMEOUT_MILLIS_MAX)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}


static void _disable_safety_pins(void)
{
    digitalWrite(MOTOR_ENABLE_LEFT, LOW);
    digitalWrite(MOTOR_ENABLE_RIGHT, LOW);
}


static void _enable_safety_pins(void)
{
    digitalWrite(MOTOR_ENABLE_LEFT, HIGH);
    digitalWrite(MOTOR_ENABLE_RIGHT, HIGH);
}