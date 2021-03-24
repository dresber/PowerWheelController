// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "led_matrix/led_matrix_display.h"
#include <MD_MAX72xx.h>
#include <SPI.h>

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

byte arrow_up[8] = {B00011000,
                    B00111100,
                    B01111110,
                    B11111111,
                    B00011000,
                    B00011000,
                    B00011000,
                    B00011000};

byte arrow_down[8] = {B00011000,
                      B00011000,
                      B00011000,
                      B00011000,
                      B11111111,
                      B01111110,
                      B00111100,
                      B00011000};

byte stop_signe[8] = {B11000011,
                      B11100111,
                      B01111110,
                      B00111100,
                      B00111100,
                      B01111110,
                      B11100111,
                      B11000011};                 


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global variables
// ------------------------------------------------ //
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, LED_CS_PIN, NR_OF_DISPLAYS);

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void _set_led_matrix_signe(byte signe[8]);


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_led_matrix(void)
{
    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, 8);
    mx.clear();
}


/**
 * 
 */
void set_led_matrix_stop(void)
{
    _set_led_matrix_signe(stop_signe);
}


/**
 * 
 */
void set_led_matrix_forward(void)
{
    _set_led_matrix_signe(arrow_up);
}


/**
 * 
 */
void set_led_matrix_backward(void)
{
    _set_led_matrix_signe(arrow_down);
}


void _set_led_matrix_signe(byte signe[8])
{
    mx.clear();

    for (int i=0; i<8; i++)
    {
        mx.setRow(0,i, signe[i]);
    }
}
