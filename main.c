/*
 * File:   main.c
 * Author: Abhiram
 *
 * Created on 12 November, 2024, 8:36 AM
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
#include "dashboard.h"
#include "view_log.h"
#include "set_time.h"
#include "download_log.h"
#include "clear_log.h"


void init_config(void)
{
	init_adc();
	init_clcd();
	init_matrix_keypad();
	init_i2c();
    init_ds1307();
	init_uart();
}


void eeprom_storing(void)
{
    // Increment event count
    event++;

    // Calculate EEPROM address based on event
    if (event > 10) 
    {
        eeprom_add = (event % 10) * 10; // Overwrite after 10 events
    }

    // Store time (excluding ':')
    for (int i = 0; time[i] != '\0'; i++) 
    {
        if (time[i] != ':') 
        {
            write_external_eeprom(eeprom_add++, time[i]);
        }
    }

    // Store gear position
    for (int i = 0; i < 2; i++) 
    {
        write_external_eeprom(eeprom_add++, gear[gear_i][i]);
    }

    // Store speed
    write_external_eeprom(eeprom_add++, '0' + (speed / 10));
    write_external_eeprom(eeprom_add++, '0' + (speed % 10));

    // Wrap around EEPROM address if it exceeds 100
    if (eeprom_add >= 100) 
    {
        eeprom_add = 0;
    }

    // Reset store flag
    store_flag = 0;
}



void menu(void)
{
	if (disp_menu)
	{
		if (key == MK_SW2)
		{
			CLEAR_DISP_SCREEN;
			if(star == 0 & once == 0)
			{
				once = 1;
				star = 1;
				select++;
			}
			else if(star == 1 & scroll < 3)
			{
				scroll++;
				select++;
			}

			if (scroll > 3)
			{
				scroll = 3;
			}
			if (select > 4)
			{
				select = 4;
			}

		}

		if (key == MK_SW1)
		{
			CLEAR_DISP_SCREEN;
			if(star == 1 &  once == 1)
			{
				star = 0;
				once = 0;
				select--;
			}
			else if(star == 0 & scroll > 0)
			{
				scroll--;
				select--;
			}

			if (scroll < 1)
			{
				scroll = 1;
			}
			if (select < 1)
			{
				select = 1;
			}
		}

		if(menu_display_flag)
		{
			switch (scroll)
			{
			case 1:
				clcd_print(list[0], LINE1(2));
				clcd_print(list[1], LINE2(2));
				break;

			case 2:
				clcd_print(list[1], LINE1(2));
				clcd_print(list[2], LINE2(2));
				break;

			case 3:
				clcd_print(list[2], LINE1(2));
				clcd_print(list[3], LINE2(2));
				break;

			default:
				scroll = 1;
				break;
			}

			if(star)
			{
				clcd_putch('*',LINE2(0));
			}
			else
			{
				clcd_putch('*',LINE1(0));
			}
		}

	}
}


void execute_menu(void)
{
	if(select == 1)
	{
		flag1 = 1;
		//view_count = 0;
		view_log();
	}
	else if(select == 2)
	{
		flag2 = 1;
		set_time();
	}
	else if(select == 3)
	{
		flag4 = 1;
		download_log();
	}
	else if(select == 4)
	{
		flag3 = 1;
		clear_log();
	}


}



void main(void)
{
	init_config();
	while (1)
	{
		key = read_switches(STATE_CHANGE);
		get_time();

		if (dash_board_flag)
		{
			dash_board();
		}

		if (disp_menu && execute == 0)
		{
			menu();
		}

		if (execute)
		{
			execute_menu();
		}

		if (store_flag)
		{
			eeprom_storing();
		}

		

		if (key == MK_SW11)
		{
			if (dash_board_flag)
			{
				dash_board_flag = 0;
				disp_menu = 1;
				menu_display_flag = 1;
				scroll = 1;
				select = 1;
				once = 0;
				star = 0;
				CLEAR_DISP_SCREEN;
			}
			else if (disp_menu && execute == 0)
			{
				execute = 1;
				menu_display_flag = 0;
				CLEAR_DISP_SCREEN;
			}

		}

		

		if (key == MK_SW12)
		{
			if(execute)
			{
				execute = 0;
				menu_display_flag = 1;
				CLEAR_DISP_SCREEN;
			}
			else if (disp_menu && execute == 0)
			{
				disp_menu = 0;
				dash_board_flag = 1;
				CLEAR_DISP_SCREEN;
			}
			else if (flag1)
			{
				dash_board_flag = 0;
				disp_menu = 1;
				scroll = 1;
				select = 1;
				once = 0;
				star = 0;
				menu_display_flag = 1;
				execute = 0;
				flag1 = 0;
				view_count = 0;

				CLEAR_DISP_SCREEN;
			}
		}
	}
}