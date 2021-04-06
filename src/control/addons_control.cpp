// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "addons_control.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static bool _light_state = false;
static bool _alarm_light_state = false;

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_addons_control(void)
{
    pinMode(LIGHT_OUTPUT, OUTPUT);
    pinMode(ALARM_LIGHT_OUTPUT, OUTPUT);

    pinMode(LIGHT_SWITCH_INPUT, INPUT_PULLUP);
    pinMode(ALARM_LIGHT_SWITCH_INPUT, INPUT_PULLUP);    
}

/**
 * 
 */
void process_addons_control(void)
{
    static bool prev_light_btn_state = digitalRead(LIGHT_SWITCH_INPUT);
    static bool prev_alarm_light_btn_state = digitalRead(ALARM_LIGHT_SWITCH_INPUT);

    if (prev_light_btn_state != digitalRead(LIGHT_SWITCH_INPUT))
    {
        prev_light_btn_state = digitalRead(LIGHT_SWITCH_INPUT);

        if (digitalRead(LIGHT_SWITCH_INPUT) == LOW)
        {
            _light_state = !_light_state;
        }
    } 

    if (prev_alarm_light_btn_state != digitalRead(ALARM_LIGHT_SWITCH_INPUT))
    {
        prev_alarm_light_btn_state = digitalRead(ALARM_LIGHT_SWITCH_INPUT);

        if (digitalRead(ALARM_LIGHT_SWITCH_INPUT) == LOW)
        {
            _alarm_light_state = !_alarm_light_state;
        }
    }

    if(_light_state == true)
    {
        digitalWrite(LIGHT_OUTPUT, HIGH);
    }
    else
    {
        digitalWrite(LIGHT_OUTPUT, LOW);
    }

    if(_alarm_light_state == true)
    {
        digitalWrite(ALARM_LIGHT_OUTPUT, HIGH);
    }
    else
    {
        digitalWrite(ALARM_LIGHT_OUTPUT, LOW);
    }
}

/**
 * 
 */
bool get_light_state(void)
{
    return(_light_state);
}

/**
 * 
 */
bool get_alarm_light_state(void)
{
    return(_alarm_light_state);
}

/**
 * 
 */
void set_light_state(bool state)
{
    _light_state = state;
}

/**
 * 
 */
void set_alarm_light_state(bool state)
{
    _alarm_light_state = state;
}