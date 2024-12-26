/*
 * File:   clear_log.c
 * Author: Abhiram
 *
 * Created on 21 November, 2024, 5:31 PM
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "ds1307.h"
#include "rtc.h"
#include "i2c.h"
#include "uart.h"






// Function to clear logs and reset related variables.
void clear_log()
{
	if(flag3)
	{
		event = 0;
		view_count = 0;
		eeprom_add = 0;
		download_count = 0;
		clcd_print("WAIT...",LINE1(0));
		clcd_print("LOG CLEARING",LINE2(0));
		for(unsigned long int i=500000; i--;);
        clcd_print("LOG CLEARED",LINE1(0));
		clcd_print("SUCCESSFULL!!",LINE2(0));
        for(unsigned long int i=500000; i--;);
		dash_board_flag = 0;
		disp_menu = 1;
		scroll = 1;
		select = 1;
		once = 0;
		star = 0;
		menu_display_flag = 1;
		execute = 0;
		flag3 = 0;
        prev_val = 0;
		CLEAR_DISP_SCREEN;
	}
}