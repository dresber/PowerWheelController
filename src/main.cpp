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

#ifdef DEBUG_DISTANCE
#include "sensors/distance.h"
#endif // #ifdef DEBUG_DISTANCE

//#include "motor\motor_control.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define TASK_1_PROCESS_TIME 10
#define TASK_2_PROCESS_TIME 50
#define TASK_3_PROCESS_TIME 100
#define TASK_4_PROCESS_TIME 500
#define TASK_5_PROCESS_TIME 500

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void serial_task(void *pvParameters);
void process_task(void *pvParameters);
void display_task(void *pvParameters);


void serial_task(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    process_serial_rx();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void process_task(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
#ifdef DEBUG_MAIN
  digitalWrite(MAIN_LOOP, HIGH);
#endif // #ifdef DEBUG_MAIN
    process_safety();
    process_addons_control();
#ifdef DEBUG_MAIN
  digitalWrite(MAIN_LOOP, LOW);
#endif // #ifdef DEBUG_MAIN
    vTaskDelay(20 / portTICK_PERIOD_MS);  
  }
}

void display_task(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    update_display();
    vTaskDelay(500 / portTICK_PERIOD_MS);  
  }
}

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

#ifdef OS_FREERTOS
  xTaskCreate(serial_task, "serial", 128, NULL, 2, NULL);
  xTaskCreate(process_task, "process", 256, NULL, 2, NULL);
  xTaskCreate(display_task, "display", 256, NULL, 2, NULL);
  vTaskStartScheduler();
#endif // #ifdef OS_FREERTOS

}


void loop() 
{
}