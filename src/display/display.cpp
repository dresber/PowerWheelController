 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "display/display.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "display/custom_chars.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
LiquidCrystal_I2C lcd(0x27,20,4);

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
static void print_arrow_forward(void);

// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
void setup_display(void)
{
    lcd.init();
    lcd.backlight();

    lcd.createChar(0, arrow_forward_left_edge);
    lcd.createChar(1, arrow_forward_middle_top);
    lcd.createChar(2, arrow_forward_right_edge);    
    lcd.createChar(3, arrow_forward_middle_bottom);
    lcd.home();

    print_arrow_forward();    
}


/**
 * 
 */
void update_display(void)
{
}


static void print_arrow_forward(void)
{
    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(1, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(1, 1);
    lcd.write(3);
}
