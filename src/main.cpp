// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>
#include "motor\motor_control.h"

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
void set_status_information(void)
{
  ActiveMoving active_movement = get_actual_movement();
  
  int act_speed = get_actual_speed();
  int act_speed_setpoint = get_actual_speed_setpoint();

  Serial.print("motor_direction: ");
  switch (active_movement)
  {
    case MOVING_OFF:
      Serial.println("OFF;");
      break;
    case MOVING_LEFT:
      Serial.print("LEFT; motor_speed_set: ");
      Serial.print(act_speed_setpoint);
      Serial.print("; motor_speed_act: ");
      Serial.println(act_speed);
      break;
    case MOVING_RIGHT:
      Serial.print("RIGHT; motor_speed_set: ");
      Serial.print(act_speed_setpoint);
      Serial.print("; motor_speed_act: ");
      Serial.println(act_speed);
      break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  setup_motor_pins();

}


void loop() {
  int process_cnt = 0;
  int motor_cnt = 0;
  int status_cnt = 0;

  Serial.println("PowerWheelControl");

  while (true)
  {
    process_motor_inputs();

    if (motor_cnt >= 10)
    {
      process_motor_outputs();
      motor_cnt = 0;
    }

    if (process_cnt >= 50)
    {
      if (get_actual_movement() != MOVING_OFF)
      {
        digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
      }
      else
      {
        digitalWrite(LED_BUILTIN, LOW);
      }

      process_cnt = 0;

    }

    if (status_cnt >= 100)
    {
      set_status_information();
      status_cnt = 0;
    }

    process_cnt += 1;
    motor_cnt += 1;
    status_cnt += 1;
    delay(10);
  }
}