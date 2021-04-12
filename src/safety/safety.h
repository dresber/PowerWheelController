#ifndef safety_H
#define safety_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
typedef enum
{
    SAFETY_OK = 1,
    SAFETY_EMERGENCY_STOP = 2,
}SafetyState;


typedef enum
{
    OFF = 1,
    MONITOR = 2,
    CONTROL = 3,
}RemoteState;

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void setup_safety(void);
void process_safety(void);

void set_remote_state(RemoteState state);
RemoteState get_remote_state(void);
void trigger_remote_wdg(void);

void set_emergency_stop(void);
void reset_emergency_stop(void);

SafetyState get_safety_state(void);


#endif // #ifndef safety_H