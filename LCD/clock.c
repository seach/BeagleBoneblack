/*
 * LCD_TEST.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include "lcd1602.h"
#include "lcd1602.c"

using namespace std;

int second, minute, hour, dayOfWeek, dayOfMonth, month, year;

int main(int argc, char **argv)
{
	
	
	lcd_init();
	BG_OFF;
	sleep(2);
	usleep(10000);
	write_command(0x02);
	usleep(10000);
	BG_ON;
	lcd_gotoxy(1,1);
	lcd_write_char('W');
	lcd_write_char('e');
	lcd_write_char('l');
	lcd_write_char('c');
	lcd_write_char('o');
	lcd_write_char('m');
	lcd_write_char('e');
	lcd_gotoxy(10,1);
	lcd_write_char('t');
    lcd_write_char('o');
    lcd_gotoxy(1,2);
	lcd_write_char('B');
	lcd_write_char('e');
	lcd_write_char('a');
	lcd_write_char('g');
	lcd_write_char('l');
	lcd_write_char('e');
	lcd_write_char('B');
	lcd_write_char('o');
	lcd_write_char('n');
	lcd_write_char('e');
	lcd_gotoxy(12,2);
	lcd_write_char('B');
	lcd_write_char('l');
	lcd_write_char('a');
	lcd_write_char('c');
	lcd_write_char('k');
	
	sleep(10);
	BG_OFF;
	sleep(1);
	lcd_cls();
	BG_ON;
	usleep(10000);
	lcd_gotoxy(8,1);
	lcd_printf("By");
	lcd_gotoxy(5,2);
	lcd_printf("S.E.A.C.");
	sleep(10);
	BG_OFF;
	sleep(1);
	lcd_cls();
	BG_ON;
	
	while (1)
	{
			time_t now = time(0);
			tm *ltm = localtime(&now);

			lcd_gotoxy(4,1);
			lcd_printf("%02u-%02u-%04u",ltm->tm_mday, ltm->tm_mon, 1900+ltm->tm_year);
			lcd_gotoxy(5,2);
			lcd_printf("%02u:%02u:%02u",ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
//			printf("%02d-%02d-%02d\n",ltm->tm_mday, ltm->tm_mon, 1900 +ltm->tm_year);
//			printf("%02d:%02d:%02d\n",ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
			usleep(100000);
	}
	BG_OFF;
	return 0;
	lcd_unload();
}
