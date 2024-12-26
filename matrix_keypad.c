/*
 * File:   matrix_keypad.c
 * Author: Abhiram
 *
 * Created on 12 November, 2024, 8:32 AM
 */


#include <xc.h>
#include "matrix_keypad.h"

void init_matrix_keypad(void)
{
	/* Config PORTB as digital */
	ADCON1 = 0x0F;

	/* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
	TRISB = 0x1E;

	/* Set PORTB input as pull up for columns */
	RBPU = 0;

	MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0;
}

unsigned char scan_key(void)
{
	ROW1 = LO;
	ROW2 = HI;
	ROW3 = HI;

	if (COL1 == LO)
	{
		return 1; //switch1 pressed
	}
	else if (COL2 == LO)
	{
		return 4; //switch4 pressed
	}
	else if (COL3 == LO)
	{
		return 7; //switch7 pressed
	}
	else if (COL4 == LO)
	{
		return 10;//switch10 pressed
	}

	ROW1 = HI;
	ROW2 = LO;
	ROW3 = HI;

	if (COL1 == LO)
	{
		return 2; //switch2 pressed
	}
	else if (COL2 == LO)
	{
		return 5; //switch5 pressed
	}
	else if (COL3 == LO)
	{
		return 8; //switch8 pressed
	}
	else if (COL4 == LO)
	{
		return 11; //switch11 pressed
	}

	ROW1 = HI;
	ROW2 = HI;
	ROW3 = LO;
	/* TODO: Why more than 2 times? */
	ROW3 = LO;

	if (COL1 == LO)
	{
		return 3; //switch3 pressed
	}
	else if (COL2 == LO)
	{
		return 6; //switch6 pressed
	}
	else if (COL3 == LO)
	{
		return 9; //switch9 pressed
	}
	else if (COL4 == LO)
	{
		return 12; //switch12 pressed
	}

	return 0xFF;
}

unsigned char read_switches(unsigned char detection_type)
{
	static unsigned char once = 1, key;

	if (detection_type == STATE_CHANGE)
	{
		key = scan_key(); 
		if(key != 0xFF && once  )
		{
			once = 0;
			return key;
		}
		else if(key == 0xFF)
		{
			once = 1;
		}
	}
	else if (detection_type == LEVEL_CHANGE)
	{
		return scan_key();
	}

	return 0xFF;
}
