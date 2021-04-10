 // ------------------------------------------------ //
//                     imports
// ------------------------------------------------ //
#include "comm/comm.h"

#ifdef SAFETY
#include "safety/safety.h"
#endif // #ifdef SAFETY

#ifdef ADDONS_CONTROL
#include "control/addons_control.h"
#endif // #ifdef ADDONS_CONTROL

#ifdef DRIVE_CONTROL
#include "control/drive_control.h"
#endif // #ifdef DRIVE_CONTROL

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
#ifdef SAFETY
            trigger_remote_wdg();
#ifdef DEBUG_COMM
            DEBUG_OUTPUT.println("watchdog triggered");
#endif // #ifdef DEBUG_COMM
        }
        else if(cmd_string == "em_stop")
        {
            set_emergency_stop();
        }
        else if(cmd_string == "em_res")
        {
            reset_emergency_stop();
        }
        else if(cmd_string == "rem_con")
        {
            set_remote_state(CONTROL);
#ifdef DRIVE_CONTROL
            set_remote_control_enabled(true);
#endif // #ifdef DRIVE_CONTROL
        }
        else if (cmd_string == "rem_mon")
        {
            set_remote_state(MONITOR);
        }
        else if (cmd_string == "rem_off")
        {
            set_remote_state(OFF);
#ifdef DRIVE_CONTROL
            set_remote_control_enabled(false);
#endif // #ifdef DRIVE_CONTROL
#endif // #ifdef SAFETY
        }
#ifdef ADDONS_CONTROL
        else if (cmd_string == "light_tog")
        {
            set_light_state(!get_light_state());
        }
        else if (cmd_string == "alarm_tog")
        {
            set_alarm_light_state(!get_alarm_light_state());
        }
#endif // #ifdef ADDONS_CONTROL
#ifdef DRIVE_CONTROL
        else if (cmd_string == "spd_plus")
        {
            increase_speed_level();
        }
        else if (cmd_string == "spd_minus")
        {
            reduce_speed_level();
        }
        else if (cmd_string == "mov_for")
        {
            set_moving_direction(DIR_FORWARD);
        }
        else if (cmd_string == "mov_off")
        {
            set_moving_direction(DIR_OFF);
        }
        else if (cmd_string == "mov_back")
        {
            set_moving_direction(DIR_BACKWARD);
        }

#endif // #ifdef DRIVE_CONTROL
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

#ifdef DEBUG_COMM
    digitalWrite(SERIAL_RX_TASK_PIN, HIGH);
#endif // #ifdef DEBUG_COMM

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
#ifdef DEBUG_COMM
    digitalWrite(SERIAL_RX_TASK_PIN, LOW);
#endif // #ifdef DEBUG_COMM

}
