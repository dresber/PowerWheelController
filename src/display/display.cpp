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

#ifdef DRIVE_CONTROL
#include "control/drive_control.h"
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
#include "control/steering_control.h"
#endif // #ifdef STEERING_CONTROL

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
#ifdef SAFETY
static void _print_safety_state(void);
static void _print_remote_state(void);
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
static void _print_power_level(void);
#endif // #ifdef POWER_MONITOR

#ifdef ADDONS_CONTROL
static void _print_addons_control(void);
#endif // #ifdef ADDONS_CONTROL

#ifdef DRIVE_CONTROL
static void _print_speed_control(void);
static void _print_driving_direction(void);
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
static void _print_steering_direction(void);
#endif // #ifdef STEERING_CONTROL

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

    _add_custom_char(arrow_forward);
    _add_custom_char(arrow_back);
    _add_custom_char(remote_antenna_signe);
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
    _print_safety_state();
    _print_remote_state();
#endif // #ifdef SAFETY

#ifdef POWER_MONITOR
    _print_power_level();
#endif // #ifdef POWER_MONITOR

#ifdef ADDONS_CONTROL
    _print_addons_control();
#endif // #ifdef ADDONS_CONTROL

#ifdef DRIVE_CONTROL
    _print_speed_control();
    _print_driving_direction();
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
    _print_steering_direction();
#endif // #ifdef STEERING_CONTROL
}

#ifdef SAFETY
static void _print_safety_state(void)
{
    static SafetyState prev_state;
    SafetyState act_state = get_safety_state();

    if (prev_state != act_state)
    {
        prev_state = act_state;

        lcd.setCursor(8, 0);
        lcd.print("    ");

        if (act_state == SAFETY_OK)
        {
            lcd.setCursor(9, 0);
            lcd.print("OK");
        }
        else
        {
            lcd.setCursor(8, 0);
            lcd.print("STOP");
        }
    }
}


static void _print_remote_state(void)
{
    static RemoteState prev_state;
    RemoteState act_state = get_remote_state();

    if (prev_state != act_state)
    {
        lcd.setCursor(14, 2);
        lcd.write(remote_antenna_signe.char_nr);
        lcd.setCursor(16, 2);

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
    static int16_t prev_voltage_mv;
    int16_t act_power_level = get_actual_power_level();
    int16_t act_voltage_mv = get_actual_battery_voltage();

    if (prev_power_level != act_power_level)
    {
        prev_power_level = act_power_level;

        lcd.setCursor(19, 0);
        lcd.print("%");
        lcd.setCursor(16, 0);
        lcd.print(act_power_level);
    }

    if (prev_voltage_mv != act_voltage_mv)
    {
        prev_voltage_mv = act_voltage_mv;

        lcd.setCursor(19, 1);
        lcd.print("V");
        lcd.setCursor(16, 1);
        lcd.print(act_voltage_mv/1000);
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


#ifdef DRIVE_CONTROL
static void _print_speed_control(void)
{
    static int16_t prev_speed_level = -1;
    int16_t speed_level = get_actual_speed_level();

    if (prev_speed_level != speed_level)
    {
        prev_speed_level = speed_level;

        lcd.setCursor(0, 3);
        lcd.print("+  ");
        lcd.print(speed_level);
        lcd.print("  -");
    }
}

static void _print_driving_direction(void)
{
    static DriveDirection prev_direction;
    DriveDirection act_direction = get_moving_direction();

    if (prev_direction != act_direction)
    {
        prev_direction = act_direction;

        lcd.setCursor(3, 0);
        lcd.print(" ");
        lcd.setCursor(3, 1);
        lcd.print(" ");
        lcd.setCursor(3, 2);
        lcd.print(" ");

        switch (act_direction)
        {
            case DIR_OFF:
                lcd.setCursor(3, 1);
                lcd.print("-");
                break;
            case DIR_FORWARD:
                lcd.setCursor(3, 0);
                lcd.print("F");
//                lcd.write(arrow_forward.char_nr);
                break;
            case DIR_BACKWARD:
                lcd.setCursor(3, 2);
                lcd.print("B");
//                lcd.write(arrow_back.char_nr);
                break;
        }
    }
}
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
static void _print_steering_direction(void)
{
    static SteeringDirection prev_direction;
    SteeringDirection act_direction = get_steering_direction();

    if (prev_direction != act_direction)
    {
        prev_direction = act_direction;

        lcd.setCursor(1, 1);
        lcd.print(" ");
        lcd.setCursor(5, 1);
        lcd.print(" ");

        switch (act_direction)
        {
            case STEER_LEFT:
                lcd.setCursor(1, 1);
                lcd.print("L");
                break;
            case STEER_RIGHT:
                lcd.setCursor(5, 1);
                lcd.print("R");
                break;
            case STEER_STRAIGHT:
                break;
        }
    }
}
#endif // #ifdef STEERING_CONTROL


static void _add_custom_char(CustomChar custom_char)
{
    lcd.createChar(custom_char.char_nr, custom_char.char_pixels);
}