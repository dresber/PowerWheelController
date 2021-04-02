#ifndef comm_H
#define comm_H
// ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "project_config.h"
#include <Arduino.h>

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
void setup_comm_serial(void);
void process_serial_rx(void);

void send_tx_msg_with_data(String command, String data);


#endif // #ifndef comm_H