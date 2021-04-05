// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "voltage_monitor.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
int16_t get_actual_power_level(void)
{
    uint32_t adc_raw_value = analogRead(MAIN_POWER_PIN);
    uint32_t adc_voltage = 0;
    uint32_t main_voltage = 0;
    uint16_t power_level = 0;

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

    main_voltage = (R1_VALUE * adc_voltage / R2_VALUE) + adc_voltage;

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
