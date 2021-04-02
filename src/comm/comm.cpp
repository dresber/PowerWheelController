 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "comm/comm.h"

// ------------------------------------------------ //
//                  definitions
// ------------------------------------------------ //
#define MAX_SIZE_OF_CMD         50
#define END_CMD_CHAR            0x0A
#define CMD_VALUE_SEPARATOR     0x20

// ------------------------------------------------ //
//                  type definitions
// ------------------------------------------------ //


// ------------------------------------------------ //
//                  global vars
// ------------------------------------------------ //


// ------------------------------------------------ //
//              function prototypes
// ------------------------------------------------ //
void process_command(char cmd_buffer[]);


// ------------------------------------------------ //
//              function definitions
// ------------------------------------------------ //
void setup_comm_serial(void)
{
    COMM_OUTPUT.begin(9600);
}


/**
 * 
 */
void send_tx_msg_with_data(String command, String data)
{
    uint8_t cmd_i = 0;
    uint8_t string_i = 0;

    for(string_i = 0; string_i < command.length(); string_i++)
    {
        COMM_OUTPUT.write(command[string_i]);
        cmd_i++;
    }

    COMM_OUTPUT.write(CMD_VALUE_SEPARATOR);
    cmd_i++;

    for(string_i = 0; string_i < data.length(); string_i++)
    {
        COMM_OUTPUT.write(data[string_i]);
        cmd_i++;
    }

    COMM_OUTPUT.write(END_CMD_CHAR);
}


/**
 * 
 */
void process_command(char cmd_buffer[])
{

    bool cmd_found = false;
    int i = -1;
    String cmd_string = "";
    String data_string = "";

    do
    {
        i++;

        if(cmd_found == false)
        {
            if(cmd_buffer[i] == ';')
            {
#ifdef DEBUG_COMM
                DEBUG_OUTPUT.println("cmd found");
#endif // #ifdef DEBUG_COMM
                cmd_found = true;
                break;                   
            }
            else if (cmd_buffer[i] == ' ')
            {
#ifdef DEBUG_COMM
                DEBUG_OUTPUT.println("value sep");
#endif // #ifdef DEBUG_COMM
                cmd_found = true;     
            }
            else
            {
                cmd_string += cmd_buffer[i];
            }
        }
        else 
        {
            if (cmd_buffer[i] != ';')
            {
                data_string += cmd_buffer[i];
            }
            else
            {
                break;
            }
        }
    } while(i < MAX_SIZE_OF_CMD - 2);

    if(cmd_found == true)
    {
        if(cmd_string == "wdg_trig")
        {
#ifdef DEBUG_COMM
            DEBUG_OUTPUT.println("watchdog triggered");
#endif // #ifdef DEBUG_COMM
        }
    }
    else
    {
#ifdef DEBUG_COMM
        DEBUG_OUTPUT.println("no command found");
#endif // #ifdef DEBUG_COMM
    }
}


/**
 * 
 */
void process_serial_rx(void)
{
    static int cmd_index = 0;
    static char rx_cmd[MAX_SIZE_OF_CMD];

#ifdef DEBUG
    digitalWrite(SERIAL_RX_TASK_PIN, HIGH);
#endif // #ifdef DEBUG

    while(COMM_OUTPUT.available()) {

        char c = (char)COMM_OUTPUT.read();

#ifdef DEBUG_COMM
        DEBUG_OUTPUT.print(c);
#endif // #ifdef DEBUG_COMM

        if(c != '\r')
        {
            if(c=='\n') 
            {
                rx_cmd[cmd_index] = ';';
                cmd_index = 0;

                process_command(rx_cmd);
            } 
            else 
            {      
                rx_cmd[cmd_index] = c;
                cmd_index++;
            }
        }
    }
#ifdef DEBUG
    digitalWrite(SERIAL_RX_TASK_PIN, LOW);
#endif // #ifdef DEBUG

}
