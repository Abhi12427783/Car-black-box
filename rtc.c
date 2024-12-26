/*
 * File:   rtc.c
 * Author: Abhiram
 *
 * Created on 16 November, 2024, 1:36 PM
 */


#include <xc.h>
#include "rtc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"


unsigned char clock_reg[3];  
unsigned char time[9];  




void display_time(void)
{
    //clcd_print("time", LINE1(2));
    clcd_print(time, LINE2(0));  
    
    if (clock_reg[0] & 0x40)  // Check if the 6th bit of the hour register indicates 12-hour format
    {
       // If the 5th bit is set, it's PM; otherwise, it's AM
        if (clock_reg[0] & 0x20)  // Check if the 5th bit of the hour register indicates PM
        {
            clcd_print("PM", LINE2(12));  // Display "PM" on the LCD at column 12 of line 2
        }
        else
        {
            clcd_print("AM", LINE2(12));  // Display "AM" on the LCD at column 12 of line 2
        }
    }
}

// Function to retrieve the current time from the DS1307 RTC
 void get_time(void)
{
    // Read the current hour, minute, and second from the DS1307 RTC
    clock_reg[0] = read_ds1307(HOUR_ADDR);  // Read the hour register from DS1307
    clock_reg[1] = read_ds1307(MIN_ADDR);   // Read the minute register from DS1307
    clock_reg[2] = read_ds1307(SEC_ADDR);   // Read the second register from DS1307

    // Format the hour part and store it in the `time` array
    if (clock_reg[0] & 0x40)  // If the clock is in 12-hour mode (6th bit of hour register is set)
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);  // Extract the 12-hour format value (1 or 2)
        time[1] = '0' + (clock_reg[0] & 0x0F);  // Extract the hour value (0-12)
    }
    else  // If the clock is in 24-hour mode
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);  // Extract the hour value (00-23)
        time[1] = '0' + (clock_reg[0] & 0x0F);  // Extract the hour value (0-9)
    }
    time[2] = ':';  // Add the colon separator for time format
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);  // Extract the tens place of the minute
    time[4] = '0' + (clock_reg[1] & 0x0F);  // Extract the ones place of the minute
    time[5] = ':';  // Add the colon separator for time format
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);  // Extract the tens place of the second
    time[7] = '0' + (clock_reg[2] & 0x0F);  // Extract the ones place of the second
    time[8] = '\0';  // Add the null terminator to the end of the time string
}


