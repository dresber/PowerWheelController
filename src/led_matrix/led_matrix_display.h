#ifndef led_matrix_display_H
#define led_matrix_display_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include <Arduino.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define LED_CS_PIN 10
#define NR_OF_DISPLAYS 1

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //



// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //

void setup_led_matrix(void);

void set_led_matrix_stop(void);
void set_led_matrix_forward(void);
void set_led_matrix_backward(void);


#endif //#ifndef led_matrix_display_H
