#ifndef MAIN_H
#define MAIN_H


extern char gear[9][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5", "C "};
extern unsigned char time[9];
extern unsigned int store_flag = 0;
unsigned int eeprom_add = 0x00;
extern unsigned int event = 0;
extern unsigned int gear_i = 0;
extern unsigned int prev_val = 0;
extern unsigned char key = 0;
extern unsigned char dash_board_flag = 1;
extern unsigned short adc_value, speed;

extern unsigned int scroll = 1, select = 1, once = 0;
extern unsigned int disp_menu = 0,star = 0,execute = 0;
extern unsigned int menu_display_flag = 0;
extern unsigned int flag1, flag2, flag3, flag4;
extern unsigned char log[10];

char list[4][15] = {"VIEW LOG      ", "SET TIME      ", "DOWNLOAD LOG  ", "CLEAR LOG     "};
extern unsigned int view_count = 0;
unsigned int download_count = 0;

static unsigned int seconds, minutes,hours,once1=0;
unsigned int blink = 0, select_field = 1;

//void update_speed(void);
//void handle_gear_control(void);
//void display_dashboard(void);
//void dash_board(void);
void eeprom_storing(void);
void menu(void);
void execute_menu(void);
void view_log(void);
void set_time(void);
void download_log(void);
void clear_log();


#endif
