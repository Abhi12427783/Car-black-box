/*
 * File:   dasboard.c
 * Author: Abhiram
 *
 * Created on 21 November, 2024, 4:33 PM
 */

#include <xc.h>
//#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "ds1307.h"
#include "rtc.h"
#include "i2c.h"
#include "uart.h"


unsigned int gear_i = 0;
unsigned short adc_value, speed;
unsigned char key = 0;
char gear[9][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5", "C "};
unsigned char dash_board_flag = 1;
unsigned int store_flag = 0;
unsigned int prev_val = 0;


// Function to update the vehicle speed displayed on the dashboard.
void update_speed(void)
{
    // Read ADC value and calculate speed
    adc_value = read_adc(CHANNEL4);
    
    // Convert ADC value to speed by dividing by 10.
    speed = adc_value / 10;

    // Limit the speed to a maximum of 99
    if (speed > 99)
    {
        speed = 99;
    }

    // Display the speed on the dashboard
    clcd_putch('0' + (speed / 10), LINE2(14));
    clcd_putch('0' + (speed % 10), LINE2(15));
}


// Function to handle gear control based on user input.
void handle_gear_control(void)
{
    if (key == MK_SW1) // Increment gear
    {
        if (gear_i < 7)
        {
            gear_i++;
        }
        else if (gear_i == 8) // Reset to first gear if neutral
        {
            gear_i = 1;
        }
        if(prev_val != gear_i)
        {
         store_flag = 1;
         prev_val = gear_i;
        }
    }
    else if (key == MK_SW2) // Decrement gear
    {
        if (gear_i > 1)
        {
            gear_i--;
        }
        else if (gear_i == 8) // Reset to first gear if neutral
        {
            gear_i = 1;
        }
        if(prev_val != gear_i)
        {
         store_flag = 1;
         prev_val = gear_i;
        }
    }
    else if (key == MK_SW3) // Set to neutral
    {
        
        gear_i = 8;
        if(prev_val != gear_i)
        {
         store_flag = 1;
         prev_val = gear_i;
        }
    }
}

 // Function to display the dashboard information.
void display_dashboard(void)
{
    // Display header
    clcd_print("TIMER     EV  SP", LINE1(0));

    // Display time
    display_time();

    // Display gear
    clcd_print(gear[gear_i], LINE2(10));
}


// Main dashboard function to update and display data.
void dash_board(void)
{
    if (!dash_board_flag)
    {
        return; // Exit if dashboard is not active
    }

    // Update speed
    update_speed();

    // Handle gear control
    handle_gear_control();

    // Display the dashboard information
    display_dashboard();
}