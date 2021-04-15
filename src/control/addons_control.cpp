// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "addons_control.h"

#ifdef OS_FREERTOS
#include <Arduino_FreeRTOS.h>
#endif // #ifdef OS_FREERTOS

#ifdef BUZZER_AVAILABLE
#include "control/tone_notes.h"
#endif // #ifdef BUZZER_AVAILABLE

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define MAX_BUZZER_QUEUE 5

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static bool _light_state = false;
static bool _alarm_light_state = false;

#ifdef BUZZER_AVAILABLE
static volatile uint8_t _conn_buzzer_cnt = 0;
static volatile uint8_t _disconn_buzzer_cnt = 0;
#endif // #ifdef BUZZER_AVAILABLE

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
    pinMode(BUZZER_PWM_OUTPUT, OUTPUT);

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

#ifdef BUZZER_AVAILABLE
/**
 * 
 */
void process_buzzer(void)
{
    if(_conn_buzzer_cnt > 0)
    {
#ifdef DEBUG_BUZZER
        DEBUG_OUTPUT.println("play connection sound");
#endif // #ifdef DEBUG_BUZZER
        tone(BUZZER_PWM_OUTPUT, NOTE_F6);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        tone(BUZZER_PWM_OUTPUT, NOTE_F7);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        noTone(BUZZER_PWM_OUTPUT);

        _conn_buzzer_cnt -= 1;
    }

    if(_disconn_buzzer_cnt > 0)
    {
#ifdef DEBUG_BUZZER
        DEBUG_OUTPUT.println("play disconnection sound");
#endif // #ifdef DEBUG_BUZZER
        tone(BUZZER_PWM_OUTPUT, NOTE_F7);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        tone(BUZZER_PWM_OUTPUT, NOTE_F6);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        noTone(BUZZER_PWM_OUTPUT);

        _disconn_buzzer_cnt -= 1;
    }

}

/**
 * 
 */
void play_buzzer_sound(BuzzerSounds sound_type)
{
    switch(sound_type)
    {
        case BUZZ_CONNECTING_REMOTE:
            if (_conn_buzzer_cnt < MAX_BUZZER_QUEUE)
            {
#ifdef DEBUG_BUZZER
                DEBUG_OUTPUT.println("add connection sound to playlist");
#endif // #ifdef DEBUG_BUZZER
                _conn_buzzer_cnt += 1;
            }
            break;
        case BUZZ_DISCONNECTING_REMOTE:
            if (_disconn_buzzer_cnt < MAX_BUZZER_QUEUE)
            {
#ifdef DEBUG_BUZZER
                DEBUG_OUTPUT.println("add disconnecting sound to playlist");
#endif // #ifdef DEBUG_BUZZER
                _disconn_buzzer_cnt += 1;
            }
            break;
    }
}
#endif // #ifdef BUZZER_AVAILABLE