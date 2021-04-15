#ifndef addons_control_H
#define addons_control_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define LIGHT_OUTPUT 24
#define ALARM_LIGHT_OUTPUT 25
#define BUZZER_PWM_OUTPUT 4

#define LIGHT_SWITCH_INPUT 38
#define ALARM_LIGHT_SWITCH_INPUT 39

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
#ifdef BUZZER_AVAILABLE
typedef enum
{
    BUZZ_CONNECTING_REMOTE = 0,
    BUZZ_DISCONNECTING_REMOTE = 1,
}BuzzerSounds;
#endif // #ifdef BUZZER_AVAILABLE
// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void setup_addons_control(void);
void process_addons_control(void);
#ifdef BUZZER_AVAILABLE
void process_buzzer(void);
void play_buzzer_sound(BuzzerSounds sound_type);
#endif // #ifdef BUZZER_AVAILABLE

bool get_light_state(void);
bool get_alarm_light_state(void);

void set_light_state(bool state);
void set_alarm_light_state(bool state);

#endif // #ifndef addons_control_H