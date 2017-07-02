/*
 * LCD_TEST.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lcd1602.h"
#include "lcd1602.c"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd;
    struct ifreq ifr;
       
    char iface[] = "wlan0";
       
//   if (argc>1)
//   {
//		iface[] = argv[1];
//	 }
		
    lcd_init();
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
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);

    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;

    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    sleep(10);
    lcd_cls();
    usleep(10000);
    lcd_gotoxy(2,1);
    lcd_printf("By  S.E.A.C.");
    lcd_gotoxy(1,2);
    lcd_printf("%s", inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );

    //display result
    //printf("%s - %s\n" , iface , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );

    sleep(10);
	BG_OFF;
    return 0;

    lcd_unload();

}

