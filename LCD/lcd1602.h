/*
 * lcd1602.h
 * 
 * 
 */
#ifndef _lcd1602_H_
#define _lcd1602_H_


void write_command(int command);
void write_data(int dat);
void lcd_gotoxy(int x, int y);
void lcd_write_char( int dat);
void lcd_cls(void);
void lcd_printf(const char *fmt, ...);
void lcd_init(void);
void lcd_unload(void);

#endif // _lcd1602_H_
