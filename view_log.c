/*
 * File:   view_log.c
 * Author: Abhiram
 *
 * Created on 21 November, 2024, 4:48 PM
 */


#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "ds1307.h"
#include "rtc.h"
#include "i2c.h"
#include "uart.h"



unsigned char log[10];
unsigned int event = 0;
unsigned char key = 0;
unsigned int view_count = 0;
unsigned int disp_menu = 0,star = 0,execute = 0;
unsigned int menu_display_flag = 0;
unsigned int scroll = 1, select = 1, once = 0;
unsigned char dash_board_flag = 1;
unsigned int flag1, flag2, flag3, flag4;

void view_log(void)
{
	if (flag1)
	{
		int start_log, total_log;
		int address;

		if (event > 10)
		{
			start_log = event % 10;
			total_log = 10;
		}
		else
		{
			start_log = 0;
			total_log = event;
		}

		address = (start_log + view_count) % total_log * 10;

		if (event == 0)
		{
			dash_board_flag = 0;
			disp_menu = 1;
			scroll = 1;
			select = 1;
			once = 0;
			star = 0;
			menu_display_flag = 1;
			execute = 0;
			clcd_print("NO LOGS", LINE1(0));
			clcd_print("AVAILABLE :(", LINE2(0));
			for (unsigned long int i = 500000; i--;);
			CLEAR_DISP_SCREEN;
		}

		else
		{
			// Read the log from EEPROM
			for (int i = 0; i < 10; i++)
			{
				log[i] = read_external_eeprom(address + i);
			}

			// Display the log
			clcd_print("#   VIEW LOG", LINE1(0));
			clcd_putch('0' + view_count, LINE2(0));
			clcd_putch(log[0], LINE2(2));
			clcd_putch(log[1], LINE2(3));
			clcd_putch(':', LINE2(4));
			clcd_putch(log[2], LINE2(5));
			clcd_putch(log[3], LINE2(6));
			clcd_putch(':', LINE2(7));
			clcd_putch(log[4], LINE2(8));
			clcd_putch(log[5], LINE2(9));
			clcd_putch(log[6], LINE2(11));
			clcd_putch(log[7], LINE2(12));
			clcd_putch(log[8], LINE2(14));
			clcd_putch(log[9], LINE2(15));

			// Handle key inputs
			if (event > 10)
			{
				if (key == MK_SW2 && view_count < 9)
				{
					view_count++;
					CLEAR_DISP_SCREEN;
				}
			}
			else
			{
				if (key == MK_SW2 && view_count < event - 1)
				{
					view_count++;
					CLEAR_DISP_SCREEN;
				}
			}

			if (key == MK_SW1 && view_count > 0)
			{
				view_count--;
				CLEAR_DISP_SCREEN;
			}

		}
	}
}
