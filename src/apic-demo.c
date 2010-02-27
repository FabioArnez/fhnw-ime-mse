/*------------------
 apic-demo
 (c) H.Buchmann FHNW 2009
 $Id$
--------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
int main()
{
 unsigned data=0x12345678;
 unsigned* APIC_VERSION=(unsigned*)0xfee00030;
 ascii_printf(Screen,"VERSION=%x\n",*APIC_VERSION);
 return 0;
} 
