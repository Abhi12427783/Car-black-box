/*
 * File:   download_log.c
 * Author: Abhiram
 *
 * Created on 21 November, 2024, 5:22 PM
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
//#include "dashboard.h"







void download_log(void)
{
	int download_address = 0;
	unsigned char dlog[14] = {};

	if (flag4 && event > 0)
	{
		clcd_print("DOWNLOADING LOG...", LINE1(0));
		for (unsigned long int l = 500000; l--;);

		
		if (event > 10)
		{
			download_count = 10;
		}
		else
		{
			download_count = event;
		}

		puts("  TIME   EV SP\n\r");
		puts("\n\r");

		for (int i = 0; i < download_count; i++)
		{
			int k = 0, j = 0;

			
			if (event > 10)
			{
				download_address = ((event % 10) + i) % 10 * 10;
			}
			else
			{
				download_address = i * 10;
			}

			while (j < 14)
			{
				if (j == 2 || j == 5)
				{
					dlog[j] = ':';
					j++;
				}
				else if (j == 8 || j == 11)
				{
					dlog[j] = ' ';
					j++;
				}
				else
				{
					dlog[j] = read_external_eeprom(download_address + k++);
					j++;
				}
			}
			dlog[14] = '\0';

			puts(dlog);
			puts("\n\r");
		}
		CLEAR_DISP_SCREEN;
		clcd_print("SUCCESSFULLY  ", LINE1(0));
        clcd_print("DOWNLOADED..  ", LINE2(3));
		for (unsigned long int l = 500000; l--;);
		flag4 = 0;
		disp_menu = 1;
		menu_display_flag = 1;
		scroll = 1;
		select = 1;
		once = 0;
		star = 0;
		dash_board_flag = 0;
		execute = 0;
		CLEAR_DISP_SCREEN;
	}
	else if (flag4 && event == 0)
	{
		clcd_print("NO LOGS", LINE1(0));
		clcd_print("TO DOWNLOAD  ", LINE2(0));
		for (unsigned long int l = 500000; l--;);
		disp_menu = 1;
		menu_display_flag = 1;
		scroll = 1;
		select = 1;
		once = 0;
		star = 0;
		dash_board_flag = 0;
		execute = 0;
		CLEAR_DISP_SCREEN;
	}
}