/*
 * File:   set_time.c
 * Author: Abhiram
 *
 * Created on 21 November, 2024, 5:16 PM
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







void set_time(void)
{
	unsigned char key_time;
	if(once1 == 0)
	{
		hours = (time[0] - '0') * 10 + (time[1] - '0');
		minutes = (time[3] - '0') * 10 + (time[4] - '0');
		seconds = (time[6] - '0') * 10 + (time[7] - '0');
		once1 = 1;
	}

	while(flag2)
	{
		key_time = read_switches(STATE_CHANGE);
		clcd_print("HH:MM:SS", LINE1(0));
		if (blink++ < 800)
		{
			clcd_putch((hours / 10) + '0', LINE2(0));
			clcd_putch((hours % 10) + '0', LINE2(1));
			clcd_putch(':', LINE2(2));
			clcd_putch((minutes / 10) + '0', LINE2(3));
			clcd_putch((minutes % 10) + '0', LINE2(4));
			clcd_putch(':', LINE2(5));
			clcd_putch((seconds / 10) + '0', LINE2(6));
			clcd_putch((seconds % 10) + '0', LINE2(7));
		}
		else if (blink >= 800 && blink < 2000)
		{
			if (select_field == 1)
				clcd_print("  ", LINE2(0));
			if (select_field == 2)
				clcd_print("  ", LINE2(3));
			if (select_field == 3)
				clcd_print("  ", LINE2(6));
		}
		else
		{
			blink = 0;
		}


		if (key_time == MK_SW1)
		{
			if (select_field == 1)
			{
				hours = (hours + 1) % 24;
			}
			else if (select_field == 2)
			{
				minutes = (minutes + 1) % 60;
			}
			else if (select_field == 3)
			{
				seconds = (seconds + 1) % 60;
			}
		}

		else if (key_time == MK_SW2)
		{
			select_field++;
			blink = 0;
			if (select_field > 3)
			{
				select_field = 1;
			}
		}

		else if (key_time == MK_SW11)
		{
			write_ds1307(HOUR_ADDR, (hours / 10 << 4) | hours % 10);
			write_ds1307(MIN_ADDR, (minutes / 10 << 4) | minutes % 10);
			write_ds1307(SEC_ADDR, (seconds / 10 << 4) | seconds % 10);

			for (unsigned long int i = 150000; i--;);

			flag2 = 0;
			once1 = 0;
			dash_board_flag = 1;
			disp_menu = 0;
			scroll = 1;
			select_field = 1;
			select = 1;
			once = 0;
			star = 0;
			execute = 0;
			CLEAR_DISP_SCREEN;
			break;
		}

		else if (key_time == MK_SW12)
		{

			flag2 = 0;
			once1 = 0;
			dash_board_flag = 0;
			disp_menu = 1;
			scroll = 1;
			select = 1;
			select_field = 1;
			once = 0;
			star = 0;
			menu_display_flag = 1;
			execute = 0;
			CLEAR_DISP_SCREEN;
			break;
		}
	}
}
