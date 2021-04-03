// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include <Arduino.h>

#include "project_config.h"

#ifdef COMM
#include "comm/comm.h"
#endif // #ifdef COMM

#ifdef DEBUG
#include "debug/debug.h"
#endif // #ifdef DEBUG

#ifdef CAR_DISPLAY
#include "display/display.h"
#endif // #ifdef CAR_DISPLAY

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
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);

#ifdef COMM
  setup_comm_serial();
#endif //#ifdef COMM

#ifdef DEBUG
  setup_debug_pins();
  DEBUG_OUTPUT.println("PowerWheelStarted");
#endif // #ifdef DEBUG

#ifdef CAR_DISPLAY
  setup_display();
#endif // #ifdef CAR_DISPLAY

//  setup_motor_pins();

}


void loop() 
{
  static int cnt_task1 = 0;
  static int cnt_task2 = 0;
  static int cnt_task3 = 0;
  static int cnt_task4 = 0;
  static int cnt_task5 = 0;

#ifdef DEBUG_MAIN
  digitalWrite(MAIN_LOOP, HIGH);
#endif // #ifdef DEBUG_MAIN

#ifdef COMM
  process_serial_rx();
#endif // #ifdef COMM

  if (cnt_task1 >= TASK_1_PROCESS_TIME)
  {
    cnt_task1 = 0;
  }
  else
  {
    cnt_task1++;
  }


  if (cnt_task2 >= TASK_2_PROCESS_TIME)
  {
    cnt_task2 = 0;
  }
  else
  {
    cnt_task2++;
  }

  if (cnt_task3 >= TASK_3_PROCESS_TIME)
  {
    cnt_task3 = 0;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  else
  {
    cnt_task3++;
  }

  if (cnt_task4 >= TASK_4_PROCESS_TIME)
  {
    cnt_task4 = 0;
#ifdef CAR_DISPLAY
    update_display();
#endif // #ifdef CAR_DISPLAY
  }
  else
  {
    cnt_task4++;
  }

  if (cnt_task5 >= TASK_5_PROCESS_TIME)
  {
    cnt_task5 = 0;
  }
  else
  {
    cnt_task5++;
  }

#ifdef DEBUG_MAIN
  digitalWrite(MAIN_LOOP, LOW);
#endif // #ifdef DEBUG_MAIN

  delay(1);
}