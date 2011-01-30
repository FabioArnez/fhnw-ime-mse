/*-------------------
 vga-demo example of io-mapped
 (c) H.Buchmann FHNW 2010
 $Id$
 www.osdever.net/FreeVGA/vga/crtcreg.htm
---------------------*/
#include "sys/sys.h" /* for sys_inb/sys_outb */
#define CRTADDRESS 0x3d4
#define CRTVALUE   0x3d5

typedef unsigned char byte;

static void set(byte val,byte reg)
{
 sys_outb(reg,CRTADDRESS); /* select register */
 sys_outb(val,CRTVALUE);
}

static byte get(byte reg)
{
 sys_outb(reg,CRTADDRESS);
 return sys_inb(CRTVALUE);
}


int main()
{
 /* set cursor */
 set (0,0x0a);
 set(31,0x0b);
 while(1)
 {
 }
 return 0;
}
