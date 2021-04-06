// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#include <Arduino.h>

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //
typedef struct 
{
    uint8_t char_pixels[8];
    uint8_t char_nr;
}CustomChar;



CustomChar arrow_forward_left_edge = {{B00000, B00000, B00000, B00001, B00011, B00111, B01111, B11111}, 0};
CustomChar arrow_forward_right_edge = {{B00000, B00000, B00000, B10000, B11000, B11100, B11110, B11111}, 1};
CustomChar arrow_forward_middle_top = {{B00100, B01110, B11111, B11111, B11111, B11111, B11111, B11111}, 2};
CustomChar arrow_forward_middle_bottom = {{B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111}, 3};

CustomChar remote_antenna_signe_left = {{B00000, B00000, B00000, B00000, B00001, B00011, B00011, B00011}, 4};
CustomChar remote_antenna_signe_right = {{B00011, B01111, B11100, B10011, B01111, B01100, B11011, B11011}, 5};

CustomChar light_left =  {{B00011, B01111, B11111, B11111, B11111, B11111, B01111, B00111}, 6};
CustomChar light_beams_right =  {{B00100, B01000, B10000, B11110, B11110, B10000, B01000, B00100}, 7};
  
CustomChar alarm_light_off =  {{B00000, B00000, B00000, B01110, B11111, B11111, B11111, B11111}, 8};
CustomChar alarm_light_on =  {{B00100, B10101, B00000, B01110, B11111, B11111, B11111, B11111}, 9};


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //