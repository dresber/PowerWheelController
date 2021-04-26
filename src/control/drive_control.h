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
#define DIRECTION_BACKWARD_INPUT    34
#define THROTTLE_INPUT              32

#define MOTOR_FORWARD_PWM       2
#define MOTOR_BACKWARD_PWM      3
#define MOTOR_BREAK_OUTPUT      26

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

#define MIN_DIST_AT_MIN_SPEED   10
#define MIN_DIST_AT_MAX_SPEED   100

#define BRAKE_DELAY_MILLIS_PER_DUTY_CYCLE       13
#define BRAKE_MILLIS_FOR_10_DUTY_CYCLE          100
#define ACCELARATION_MILLIS_FOR_5_DUTY_CYCLE    50
#define ACCELARATION_DUTY_CYCLE_STEPS           5

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
typedef enum
{
    DIR_FORWARD = 0,
    DIR_OFF = 1,
    DIR_BACKWARD =2,

}DriveDirection;

typedef enum
{
    MOV_STOPPED = 0,
    MOV_ACTIVE = 1,
}MovementState;
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

bool get_active_collision_warning(void);

void set_moving_direction(DriveDirection direction);
void increase_speed_level(void);
void reduce_speed_level(void);
void set_remote_control_enabled(bool enabled);
void set_throttle(bool throttle_state);

#endif // #ifndef drive_control_H