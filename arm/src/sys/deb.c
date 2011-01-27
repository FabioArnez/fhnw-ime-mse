/*--------------------
 deb(ug)
 (c) H.Buchmann FHNW 2011
 $Id: deb.h 200 2010-03-13 17:20:44Z hans.buchmann $
 see [IntegratorCM] [UART]
----------------------*/
#include "sys/deb.h"

volatile struct 
{
 unsigned DR;                         /*Data register */ 
 unsigned SR;                       /* Receive status */
 unsigned res[4];                         /* reserved */
 unsigned FR;                                 /* Flag */  
}* UART = 0x16000000;

static void deb_out(char ch)
{
 while(UART->FR&(1<<3)){} /* wait until busys cleared */
 UART->DR=ch;
}

static void deb_out_string(const char*const s)
{
 for(unsigned i=0;s[i];++i)deb_out(s[i]);
}

volatile unsigned* CM_CTRL=0x1000000c;

static void reset() __attribute__((noreturn));

static void reset()
{
 *CM_CTRL|=(1<<3); /* reset */
}

void deb_signal0()
{
 deb_out_string("Signal0\n");
 reset();
}
