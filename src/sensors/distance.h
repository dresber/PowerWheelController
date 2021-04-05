#ifndef distance_H
#define distance_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Ultrasonic.h>
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
Ultrasonic front_sensor_1(FRONT_1_TRIG_PIN, FRONT_1_SENS_PIN);
#endif // #ifdef DISTANCE_SENSOR_FRONT_1
#ifdef DISTANCE_SENSOR_FRONT_2
Ultrasonic front_sensor_2(FRONT_2_TRIG_PIN, FRONT_2_SENS_PIN);
#endif // #ifdef DISTANCE_SENSOR_FRONT_2
#ifdef DISTANCE_SENSOR_BACK	
Ultrasonic back_sensor(BACK_TRIG_PIN, BACK_SENS_PIN);
#endif // #ifdef DISTANCE_SENSOR_BACK	

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


#endif // #ifndef safety_H