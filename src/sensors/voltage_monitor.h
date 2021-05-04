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

#define MAIN_POWER_MAX_VOLTAGE 20000
#define MAIN_POWER_MIN_VOLTAGE 16300

#define MIN_DRIVE_VOLTAGE 16300
#define MIN_ACTIVATION_VOLTAGE 16800

#define ADC_RESOLUTION 1024
#define ADC_VOLTAGE_IN_UV 5000000

#define R1_VALUE 10000
#define R2_VALUE 2200

#define BATTERY_LEVEL_FILTER_SIZE 10

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void process_battery_voltage_filter(void);

int16_t get_actual_power_level(void);
int16_t get_actual_battery_voltage(void);
int16_t get_average_battery_voltage(void);
int16_t get_average_power_level(void);

bool check_if_battery_level_is_ok_to_drive(void);


#endif // #ifndef voltage_H