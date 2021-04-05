#ifndef voltage_H
#define voltage_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define MAIN_POWER_PIN A0

#define MAIN_POWER_MAX_VOLTAGE 14000
#define MAIN_POWER_MIN_VOLTAGE 11000

#define ADC_RESOLUTION 1024
#define ADC_VOLTAGE_IN_UV 5000000

#define R1_VALUE 10000
#define R2_VALUE 2200

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
int16_t get_actual_power_level(void);


#endif // #ifndef voltage_H