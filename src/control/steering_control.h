#ifndef steering_control_H
#define steering_control_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define STEERING_LEFT_OUTPUT       27
#define STEERING_RIGHT_OUTPUT      28

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
typedef enum
{
    DIR_LEFT = 0,
    DIR_STRAIGHT = 1,
    DIR_RIGHT =2,

}SteeringDirection;


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void setup_steering_control(void);
void process_steering_control(void);

SteeringDirection get_steering_direction(void);

void set_steering_direction(SteeringDirection direction);
void set_remote_state(bool state);

#endif // #ifndef steering_control_H