#ifndef project_config_H
#define project_config_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define ADDONS_CONTROL

#define CAR_DISPLAY

#define COMM
#ifdef COMM
#define COMM_OUTPUT Serial1
#endif // #ifdef COMM

#define DEBUG
#ifdef DEBUG
#define DEBUG_OUTPUT Serial
#define DEBUG_PIN_1 49
#define DEBUG_PIN_2 50
#define DEBUG_PIN_3 51
#define DEBUG_PIN_4 52
#define DEBUG_PIN_5 53

#define DEBUG_MAIN
#ifdef DEBUG_MAIN
#define MAIN_LOOP DEBUG_PIN_1
#endif //#ifdef DEBUG_MAIN

#define DEBUG_DISPLAY
#ifdef DEBUG_DISPLAY
#define DISPLAY_PROCESS_PIN DEBUG_PIN_3
#endif // #ifdef DEBUG_DISPLAY

#define DEBUG_COMM
#ifdef DEBUG_COMM
#define SERIAL_RX_TASK_PIN DEBUG_PIN_2
#endif // #ifdef DEBUG_COMM
//#define DEBUG_DISTANCE
//#define DEBUG_POWER_MONITOR
#endif // #ifdef DEBUG

#define DRIVE_CONTROL

#define DISTANCE_SENSOR_FRONT_1
//#define DISTANCE_SENSOR_FRONT_2
//#define DISTANCE_SENSOR_BACK

#define OS_FREERTOS

#define SAFETY
#ifdef SAFETY
#define WDG_TRIG_TIMEOUT_MILLIS_MAX 210
#endif // #ifdef SAFETY

#define STEERING_CONTROL

#define POWER_MONITOR


// ------------------------------------------------ //
//                   PINNING
// ------------------------------------------------ //
#define MOTOR_ENABLE_RIGHT      22
#define MOTOR_ENABLE_LEFT       23



#endif //#ifndef project_config_H