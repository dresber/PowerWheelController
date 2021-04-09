 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "display/display.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "display/custom_chars.h"

#ifdef ADDONS_CONTROL
#include "control/addons_control.h"
#endif // #ifdef ADDONS_CONTROL

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

#ifdef ADDONS_CONTROL
static void _print_addons_control(void);
#endif // #ifdef ADDONS_CONTROL

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
    _add_custom_char(light_left);
    _add_custom_char(light_beams_right);
    _add_custom_char(alarm_light_off);
    _add_custom_char(alarm_light_on);

    lcd.home();

//    print_arrow_forward();    
}


/**
 * 
 */
void update_display(void)
{
#ifdef SAFETY
    print_safety_state();
    print_remote_state();
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
    _print_power_level();
#endif // #ifdef POWER_MONITOR

#ifdef ADDONS_CONTROL
    _print_addons_control();
#endif // #ifdef ADDONS_CONTROL

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
    static SafetyState prev_state;
    SafetyState act_state = get_safety_state();

    if (prev_state != act_state)
    {
        prev_state = act_state;

        lcd.setCursor(8, 0);
        lcd.print("    ");

        if (act_state == OK)
        {
            lcd.setCursor(9, 0);
            lcd.print("OK");
        }
        else if (act_state == HALT)
        {
            lcd.setCursor(8, 0);
            lcd.print("HALT");
        }
        else
        {
            lcd.setCursor(8, 0);
            lcd.print("STOP");
        }
    }
}


static void print_remote_state(void)
{
    static RemoteState prev_state;
    RemoteState act_state = get_remote_state();

    if (prev_state != act_state)
    {
        lcd.setCursor(13, 2);
        lcd.write(remote_antenna_signe_left.char_nr);
        lcd.write(remote_antenna_signe_right.char_nr);
        lcd.setCursor(15, 2);

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
}
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
static void _print_power_level(void)
{
    static int16_t prev_power_level;
    int16_t act_power_level = get_actual_power_level();

    if (prev_power_level != act_power_level)
    {
        prev_power_level = act_power_level;

        lcd.setCursor(19, 0);
        lcd.print("%");
        lcd.setCursor(16, 0);
        lcd.print(get_actual_power_level());
    }
}
#endif // #ifdef POWER_MONITOR

#ifdef ADDONS_CONTROL
static void _print_addons_control(void)
{
    static bool blink_toggle = false;
    static bool prev_light_state = true;

    bool act_light_state = get_light_state();

    if (prev_light_state != act_light_state)
    {
        prev_light_state = act_light_state;

        lcd.setCursor(12, 3);
        lcd.print("  ");
        lcd.setCursor(12, 3);
        lcd.write(light_left.char_nr);

        if(act_light_state)
        {
            lcd.setCursor(13, 3);
            lcd.write(light_beams_right.char_nr);
        }
    }

    lcd.setCursor(19, 3);

    if(get_alarm_light_state() && blink_toggle)
    {
        lcd.write(alarm_light_on.char_nr);
    }
    else
    {
        lcd.write(alarm_light_off.char_nr);
    }

    blink_toggle = !blink_toggle;
}
#endif // #ifdef ADDONS_CONTROL

static void _add_custom_char(CustomChar custom_char)
{
    lcd.createChar(custom_char.char_nr, custom_char.char_pixels);
}