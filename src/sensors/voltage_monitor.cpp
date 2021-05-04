// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "voltage_monitor.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
typedef enum
{
    BATTERY_TOO_LOW = 0,
    BATTERY_OK = 1,
}BatteryLevelState;

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //
static BatteryLevelState _battery_state = BATTERY_TOO_LOW;

static volatile uint32_t _average_battery_voltage = 0;

// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
/**
 * 
 */
int16_t get_actual_power_level(void)
{
    uint32_t main_voltage = get_actual_battery_voltage();
    uint16_t power_level = 0;

#ifdef DEBUG_POWER_MONITOR
    DEBUG_OUTPUT.print("main_voltage: ");
    DEBUG_OUTPUT.print(main_voltage);
    DEBUG_OUTPUT.println(" mV");
#endif // #ifdef DEBUG_POWER_MONITOR

    if (main_voltage > MAIN_POWER_MIN_VOLTAGE)
    {
        power_level = (main_voltage - MAIN_POWER_MIN_VOLTAGE) * 100 / (MAIN_POWER_MAX_VOLTAGE - MAIN_POWER_MIN_VOLTAGE);
    }

    return (power_level);
}

/**
 * 
 */
int16_t get_actual_battery_voltage(void)
{
    uint32_t adc_raw_value = analogRead(MAIN_POWER_PIN);
    uint32_t adc_voltage = 0;

#ifdef DEBUG_POWER_MONITOR
    DEBUG_OUTPUT.print("adc_raw_value: ");
    DEBUG_OUTPUT.println(adc_raw_value);
#endif // #ifdef DEBUG_POWER_MONITOR

    adc_voltage = (ADC_VOLTAGE_IN_UV / ADC_RESOLUTION * adc_raw_value) / 1000;

#ifdef DEBUG_POWER_MONITOR
    DEBUG_OUTPUT.print("adc_voltage: ");
    DEBUG_OUTPUT.print(adc_voltage);
    DEBUG_OUTPUT.println(" mV");
#endif // #ifdef DEBUG_POWER_MONITOR

#ifdef DEBUG_POWER_MONITOR
    DEBUG_OUTPUT.print("main_voltage: ");
    DEBUG_OUTPUT.print(((R1_VALUE * adc_voltage / R2_VALUE) + adc_voltage));
    DEBUG_OUTPUT.println(" mV");
#endif // #ifdef DEBUG_POWER_MONITOR

    return (R1_VALUE * adc_voltage / R2_VALUE) + adc_voltage;
}

/**
 * 
 */
bool check_if_battery_level_is_ok_to_drive(void)
{
    if (_battery_state == BATTERY_TOO_LOW)
    {
        if (_average_battery_voltage > MIN_ACTIVATION_VOLTAGE)
        {
            _battery_state = BATTERY_OK;
            return (true);
        }
        return (false);    
    }
    else
    {
        if (_average_battery_voltage > MIN_DRIVE_VOLTAGE)
        {
            return (true);
        }
        else
        {
            _battery_state = BATTERY_TOO_LOW;
            return (false);
        }
    }
}


/**
 * 
 */
void process_battery_voltage_filter(void)
{
    static uint64_t average_battery_voltage_sum = 0;
    static uint32_t battery_voltage_queue[BATTERY_LEVEL_FILTER_SIZE];
    static uint16_t actual_index = 0;

    uint32_t act_voltage = get_actual_battery_voltage();

    average_battery_voltage_sum -= battery_voltage_queue[actual_index];
    average_battery_voltage_sum += act_voltage;
    battery_voltage_queue[actual_index] = act_voltage;
    actual_index = (actual_index + 1) % BATTERY_LEVEL_FILTER_SIZE;

    _average_battery_voltage = average_battery_voltage_sum / BATTERY_LEVEL_FILTER_SIZE;
}


/**
 * 
 */
int16_t get_average_battery_voltage(void)
{
    return (_average_battery_voltage);
}


/**
 * 
 */
int16_t get_average_power_level(void)
{
    uint16_t power_level = 0;

    if (_average_battery_voltage > MAIN_POWER_MIN_VOLTAGE)
    {
        power_level = (_average_battery_voltage - MAIN_POWER_MIN_VOLTAGE) * 100 / (MAIN_POWER_MAX_VOLTAGE - MAIN_POWER_MIN_VOLTAGE);
    }

    return (power_level);
}
