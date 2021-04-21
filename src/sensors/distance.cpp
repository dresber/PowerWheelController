// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "distance.h"
#include <Ultrasonic.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


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


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
#ifdef DISTANCE_SENSOR_FRONT_1
/**
 * 
 */
uint16_t get_front_sensor_1_distance_in_cm(void)
{
    return front_sensor_1.read(CM);
}
#endif // #ifdef DISTANCE_SENSOR_FRONT_1


#ifdef DISTANCE_SENSOR_FRONT_2
/**
 * 
 */
uint16_t get_front_sensor_2_distance_in_cm(void)
{
    return front_sensor_2.read(CM);
}
#endif // #ifdef DISTANCE_SENSOR_FRONT_2


#ifdef DISTANCE_SENSOR_BACK	
/**
 * 
 */
uint16_t get_back_sensor_distance_in_cm(void)
{
    return back_sensor.read(CM);
}
#endif // #ifdef DISTANCE_SENSOR_BACK	
