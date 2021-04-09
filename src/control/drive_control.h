#ifndef drive_control_H
#define drive_control_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //

#define DIRECTION_FORWARD_INPUT     33
#define DIRECITON_BACKWARD_INPUT    34

#define SPEED_PLUS_INPUT    36
#define SPEED_MINUS_INPUT   37

#define SPEED_LEVEL_1 100
#define SPEED_LEVEL_2 180
#define SPEED_LEVEL_3 220
#define SPEED_LEVEL_4 255

#define START_LEVEL_FORWARD   2
#define START_LEVEL_BACKWARD  1
#define MAX_LEVEL_FORWARD     3
#define MAX_LEVEL_BACKWARD    2
#define NR_OF_SPEED_LEVEL     4

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
typedef enum
{
    DIR_FORWARD = 0,
    DIR_OFF = 1,
    DIR_BACKWARD =2,

}DriveDirection;

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void setup_drive_control(void);
void process_drive_control(void);

DriveDirection get_moving_direction(void);
int16_t get_actual_speed_level(void);
int16_t get_actual_speed_pwm_value(void);
void set_moving_direction(DriveDirection direction);
void increase_speed_level(void);
void reduce_speed_level(void);
void set_remote_control_enabled(bool enabled);

#endif // #ifndef drive_control_H