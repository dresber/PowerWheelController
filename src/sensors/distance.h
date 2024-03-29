#ifndef distance_H
#define distance_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define FRONT_1_TRIG_PIN 42
#define FRONT_1_SENS_PIN 43
#define FRONT_2_TRIG_PIN 44
#define FRONT_2_SENS_PIN 45
#define BACK_TRIG_PIN 46
#define BACK_SENS_PIN 47


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
#ifdef DISTANCE_SENSOR_FRONT_1
uint16_t get_front_sensor_1_distance_in_cm(void);
#endif // #ifdef DISTANCE_SENSOR_FRONT_1
#ifdef DISTANCE_SENSOR_FRONT_2
uint16_t get_front_sensor_2_distance_in_cm(void);
#endif // #ifdef DISTANCE_SENSOR_FRONT_2
#ifdef DISTANCE_SENSOR_BACK	
uint16_t get_back_sensor_distance_in_cm(void);
#endif // #ifdef DISTANCE_SENSOR_BACK	

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


#endif // #ifndef distance_H