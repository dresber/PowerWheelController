// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //

#include <Arduino.h>

#include "project_config.h"

#ifdef OS_FREERTOS
#include <Arduino_FreeRTOS.h>
#endif // #ifdef OS_FREERTOS

#ifdef ADDONS_CONTROL
#include "control/addons_control.h"
#endif // #ifdef ADDONS_CONTROL

#ifdef CAR_DISPLAY
#include "display/display.h"
#endif // #ifdef CAR_DISPLAY

#ifdef COMM
#include "comm/comm.h"
#endif // #ifdef COMM

#ifdef DEBUG
#include "debug/debug.h"
#endif // #ifdef DEBUG

#ifdef SAFETY
#include "safety/safety.h"
#endif // #ifdef SAFETY

#ifdef DRIVE_CONTROL
#include "control/drive_control.h"
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
#include "control/steering_control.h"
#endif // #ifdef STEERING_CONTROL

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


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
#ifdef COMM
void serial_task(void *pvParameters);
#endif // #ifdef COMM

void process_task(void *pvParameters);

#ifdef CAR_DISPLAY
void display_task(void *pvParameters);
#endif // #ifdef CAR_DISPLAY

#ifdef BUZZER_AVAILABLE
void buzzer_task(void *pvParameters);
#endif // #ifdef BUZZER_AVAILABLE

#ifdef COMM
void serial_task(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    process_serial_rx();
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
#endif // #ifdef COMM

void process_task(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
#ifdef DEBUG_MAIN
    digitalWrite(MAIN_LOOP, HIGH);
#endif // #ifdef DEBUG_MAIN
#ifdef SAFETY
    process_safety();
#endif //#ifdef SAFETY
    process_addons_control();
#ifdef DRIVE_CONTROL
    process_drive_control();
#endif // #ifdef DRIVE_CONTROL
#ifdef STEERING_CONTROL
    process_steering_control();
#endif // #ifdef STEERING_CONTROL
#ifdef DEBUG_MAIN
    digitalWrite(MAIN_LOOP, LOW);
#endif // #ifdef DEBUG_MAIN
    vTaskDelay(20 / portTICK_PERIOD_MS);  
  }
}

#ifdef CAR_DISPLAY
void display_task(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
#ifdef DEBUG_DISPLAY
    digitalWrite(DISPLAY_PROCESS_PIN, HIGH);
#endif // #ifdef DEBUG_DISPLAY
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

#ifdef POWER_MONITOR
    process_battery_voltage_filter();
#endif // #ifdef POWER_MONITOR

    update_display();
#ifdef DEBUG_DISPLAY
    digitalWrite(DISPLAY_PROCESS_PIN, LOW);
#endif // #ifdef DEBUG_DISPLAY
    vTaskDelay(500 / portTICK_PERIOD_MS);  
  }
}
#endif // #ifdef CAR_DISPLAY

#ifdef BUZZER_AVAILABLE
void buzzer_task(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
#ifdef DEBUG_BUZZER
    digitalWrite(BUZZER_PROCESS_DEBUG_PIN, HIGH);
#endif
    process_buzzer();
#ifdef DEBUG_BUZZER
    digitalWrite(BUZZER_PROCESS_DEBUG_PIN, LOW);
#endif
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }  
}
#endif // #ifdef BUZZER_AVAILABLE

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);

#ifdef ADDONS_CONTROL
  setup_addons_control();
#endif // #ifdef ADDONS_CONTROL

#ifdef COMM
  setup_comm_serial();
#endif //#ifdef COMM

#ifdef SAFETY
  setup_safety();
#else
  pinMode(MOTOR_ENABLE_LEFT, OUTPUT);
  pinMode(MOTOR_ENABLE_RIGHT, OUTPUT);
  digitalWrite(MOTOR_ENABLE_LEFT, HIGH);
  digitalWrite(MOTOR_ENABLE_RIGHT, HIGH);
#endif // #ifdef SAFETY

#ifdef DEBUG
  setup_debug_pins();
  DEBUG_OUTPUT.println("PowerWheelStarted");
#endif // #ifdef DEBUG

#ifdef CAR_DISPLAY
  setup_display();
#endif // #ifdef CAR_DISPLAY

#ifdef DRIVE_CONTROL
  setup_drive_control();
#endif // #ifdef DRIVE_CONTROL

#ifdef STEERING_CONTROL
  setup_steering_control();
#endif // #ifdef STEERING_CONTROL

#ifdef OS_FREERTOS
#ifdef COMM
  xTaskCreate(serial_task, "serial", 128, NULL, 3, NULL);
#endif // #ifdef COMM
  xTaskCreate(process_task, "process", 256, NULL, 2, NULL);
#ifdef CAR_DISPLAY
  xTaskCreate(display_task, "display", 256, NULL, 1, NULL);
#endif // #ifdef CAR_DISPLAY
#ifdef BUZZER_AVAILABLE
  xTaskCreate(buzzer_task, "buzzer", 128, NULL, 1, NULL);
#endif // #ifdef BUZZER_AVAILABLE
  vTaskStartScheduler();
#endif // #ifdef OS_FREERTOS

}


void loop() 
{
}