#ifndef project_config_H
#define project_config_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define CAR_DISPLAY
#ifdef CAR_DISPLAY

#endif // #ifdef CAR_DISPLAY

#define COMM
#ifdef COMM
#define COMM_OUTPUT Serial1
#endif // #ifdef COMM

#define DEBUG
#ifdef DEBUG
#define DEBUG_OUTPUT Serial
#define DEBUG_PIN_1 52
#define DEBUG_PIN_2 53

#define DEBUG_MAIN
#ifdef DEBUG_MAIN
#define MAIN_LOOP DEBUG_PIN_1
#endif //#ifdef DEBUG_MAIN

//#define DEBUG_COMM
#ifdef DEBUG_COMM
#define SERIAL_RX_TASK_PIN DEBUG_PIN_2
#endif // #ifdef DEBUG_COMM
#endif // #ifdef DEBUG

#define SAFETY
#ifdef SAFETY
#define WDG_TRIG_TIMEOUT_MILLIS_MAX 210
#endif // #ifdef SAFETY

// ------------------------------------------------ //
//                   PINNING
// ------------------------------------------------ //
#define MOTOR_ENABLE_RIGHT      22
#define MOTOR_ENABLE_LEFT       23



#endif //#ifndef project_config_H