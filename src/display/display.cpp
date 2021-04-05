 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "display/display.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "display/custom_chars.h"

#ifdef SAFETY
#include "safety/safety.h"
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
#include "sensors/voltage_monitor.h"
#endif // #ifdef POWER_MONITOR

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

#ifdef SAFETY
static void print_safety_state(void);
static void print_remote_state(void);
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
static void _print_power_level(void);
#endif // #ifdef POWER_MONITOR

static void _add_custom_char(CustomChar custom_char);

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

    _add_custom_char(arrow_forward_left_edge);
    _add_custom_char(arrow_forward_middle_top);
    _add_custom_char(arrow_forward_right_edge);
    _add_custom_char(arrow_forward_middle_bottom);
    _add_custom_char(remote_antenna_signe_left);
    _add_custom_char(remote_antenna_signe_right);

    lcd.home();

    print_arrow_forward();    
}


/**
 * 
 */
void update_display(void)
{
    lcd.clear();

#ifdef SAFETY
    print_safety_state();
    print_remote_state();
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
    _print_power_level();
#endif // #ifdef POWER_MONITOR

}


static void print_arrow_forward(void)
{
    lcd.setCursor(0, 0);
    lcd.write(arrow_forward_left_edge.char_nr);
    lcd.setCursor(1, 0);
    lcd.write(arrow_forward_middle_top.char_nr);
    lcd.setCursor(2, 0);
    lcd.write(arrow_forward_right_edge.char_nr);
    lcd.setCursor(1, 1);
    lcd.write(arrow_forward_middle_bottom.char_nr);
}

#ifdef SAFETY
static void print_safety_state(void)
{
    SafetyState act_state = get_safety_state();

    if (act_state == OK)
    {
        lcd.setCursor(11, 3);
        lcd.print("OK");
    }
    else if (act_state == HALT)
    {
        lcd.setCursor(10, 3);
        lcd.print("HALT");
    }
    else
    {
        lcd.setCursor(10, 3);
        lcd.print("STOP");
    }
}


static void print_remote_state(void)
{
    RemoteState act_state = get_remote_state();
    
    lcd.setCursor(15, 3);
    lcd.write(remote_antenna_signe_left.char_nr);
    lcd.write(remote_antenna_signe_right.char_nr);
    lcd.setCursor(17, 3);

    if(act_state == MONITOR)
    {
        lcd.printstr("MON");
    }
    else if (act_state == CONTROL)
    {
        lcd.printstr("CON");
    }
    else
    {
        lcd.printstr("OFF");
    }

}
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
static void _print_power_level(void)
{
    lcd.setCursor(19, 0);
    lcd.print("%");
    lcd.setCursor(15, 0);
    lcd.print(get_actual_power_level());
}
#endif // #ifdef POWER_MONITOR

static void _add_custom_char(CustomChar custom_char)
{
    lcd.createChar(custom_char.char_nr, custom_char.char_pixels);
}