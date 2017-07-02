#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "./Derek/SimpleGPIO.h"
#include "./Derek/SimpleGPIO.cpp"
#include "lcd1602.h"
#include <stdarg.h>
#include <string.h>


#define vLCD_RS 66
#define vLCD_EN 67
#define vLCD_RW 69
#define vLCD_BG 68
#define vLCD_D4 45
#define vLCD_D5 44
#define vLCD_D6 23
#define vLCD_D7 26

#define LCD_LINES 2
#define LCD_CHAR 16

#define RS_L gpio_set_value(LCD_RS, LOW)
#define RS_H gpio_set_value(LCD_RS, HIGH)
#define EN_L gpio_set_value(LCD_EN, LOW)
#define EN_H gpio_set_value(LCD_EN, HIGH)
#define RW_L gpio_set_value(LCD_RW, LOW)
#define RW_H gpio_set_value(LCD_RW, HIGH)

#define BG_OFF gpio_set_value(LCD_BG, LOW)
#define BG_ON gpio_set_value(LCD_BG, HIGH)

char const LCD_INIT_STRING[4] = {0x20 | (LCD_LINES << 2), 0xc, 1, 6};
int lcdline=1;


unsigned int LCD_RS = vLCD_RS;
unsigned int LCD_RW = vLCD_RW;
unsigned int LCD_EN = vLCD_EN;
unsigned int LCD_BG = vLCD_BG;
char lcdtxt[40];

// define  4 bits Data out: D7, D6, D5, D4
unsigned int DB[] = {vLCD_D7,vLCD_D6,vLCD_D5,vLCD_D4};

/********************************************************************/
void write_command(int command)
{
	int i,temp;
	RS_L;
	EN_L;
	temp=command & 0xf0;
	for (i=0; i < 4; i++)
	{
		if(temp&0x80)
			gpio_set_value(DB[i], HIGH);
		else 
			gpio_set_value(DB[i], LOW);
		temp <<= 1;
	}
	EN_H;
	usleep(10);
	EN_L;
	temp=(command & 0x0f)<<4;
	for (i=0; i < 4; i++)
	{
		if(temp&0x80)
			gpio_set_value(DB[i], HIGH);
		else 
			gpio_set_value(DB[i], LOW);
		temp <<= 1;
	}
	EN_H;
	usleep(10);
	EN_L;
}

/********************************************************************/
void write_data(int dat)
{
	int i=0,temp;

	RS_H;
	EN_L;
	temp=dat & 0xf0;
	for (i=0; i < 4; i++)
	{
		if(temp&0x80)
			gpio_set_value(DB[i], HIGH);
		else 
			gpio_set_value(DB[i], LOW);
		temp <<= 1;
	}
	EN_H;
	usleep(10);
	EN_L;
	temp=(dat & 0x0f)<<4;
	for (i=0; i < 4; i++)
	{
		if(temp&0x80)
			gpio_set_value(DB[i], HIGH);
		else 
			gpio_set_value(DB[i], LOW);
		temp <<= 1;
	}
	EN_H;
	usleep(10);
	EN_L;
}
void lcd_gotoxy(int x, int y)
{
	int address;
	int mx = LCD_CHAR;
	int my = LCD_LINES;
	
	if (x<0) 
		x = 0;
	else
		if (x>mx)
			x = mx;

	if (y<0) 
		y = 0;
	else
		if (y>my)
			y = my;

	switch(y) 
	{
		case 1 : 	address=0x80;
					break;
		case 2 : 	address=0xc0;
					break;
		case 3 : 	address=0x94;
					break;
		case 4 : 	address=0xd4;
					break;
   }
   lcdline = y;
   address+=x-1;
   write_command(address);
}


/********************************************************************/
void lcd_cls(void)
{
   write_command(1);
}

/********************************************************************/
void lcd_write_char( int dat)
{
	switch (dat) {
		case '\f':	write_command(1);
					lcdline=1;
					usleep(2000);
                    break;
		case '\n':	lcd_gotoxy(1,++lcdline);
					break;
		case '\b':	write_command(0x10);
					break;
		default  :	write_data(dat);
					break;
   }
	usleep(1);
}

/********************************************************************/
int strlength(char hi[])
{
    int i;
    
    for(i=0;hi[i]!='\0';i++);
        
    return i;
}

/********************************************************************/
void lcd_printf( const char *fmt, ... )
{
	int i;
	
    va_list args;
    
    va_start( args, fmt );
	vsprintf(lcdtxt,fmt, args); 
	for (i=0; i < strlength(lcdtxt); i++)
	{
		write_data(lcdtxt[i]);
	}

    va_end( args );

}

/********************************************************************/
void lcd_init()
{
	int i = 0;
		
	gpio_export(LCD_RS);
	gpio_set_dir(LCD_RS, OUTPUT_PIN);
	gpio_export(LCD_EN);
	gpio_set_dir(LCD_EN, OUTPUT_PIN);
	gpio_export(LCD_RW);
	gpio_set_dir(LCD_RW, OUTPUT_PIN);
	gpio_export(LCD_BG);
	gpio_set_dir(LCD_BG, OUTPUT_PIN);
		
	for (i=0; i < 4; i++)
	{
		gpio_export(DB[i]);
		gpio_set_dir(DB[i], OUTPUT_PIN);
	}
	usleep(1000);
	//fflush(stdout);
	RS_L;
	RW_L;
	EN_L;
    BG_ON;
    usleep(15000);
    for(i=1;i<=3;++i) {
		write_command(3);
		usleep(5000);
    }
    write_command(2);
    for(i=0;i<=3;++i)
    {
		write_command(LCD_INIT_STRING[i]);
		usleep(1000);
	}
/*	
	usleep(100);
	write_command(0x28);
	usleep(50);
	write_command(0x06);
	usleep(50);
	write_command(0x0c);
	delay(50);
	write_command(0x80);
	delay(50);
	write_command(0x01);
*/
	usleep(10000);
}

void lcd_unload(void)
{
	int i;
	
	gpio_unexport(LCD_RS);
	gpio_unexport(LCD_EN);
	gpio_unexport(LCD_RW);
	gpio_unexport(LCD_BG);
		
	for (i=0; i < 4; i++)
	{
		gpio_unexport(DB[i]);
	}
	usleep(1000);
}
