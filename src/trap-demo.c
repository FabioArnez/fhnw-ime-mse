/*----------------------
 trap-demo 
 (c) H.Buchmann FHNW 2009
 $Id: kbc-demo.c 199 2010-03-12 11:22:58Z hans.buchmann $
 TODO easy to use api 
 TODO LED control
------------------------*/
#include "sys/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/sys.h"                                       /* for sti */
#include "sys/deb.h"

static char ch='0';                  /* will be printed to the screen */

static void trap(unsigned id)
{
 deb_signal0();
 sys_inb(0x64);
 sys_inb(0x60);                 /* empty keyboard ready for next char */
 ch=(ch=='9')?'0':(ch+1);                                /* change ch */
}

static void init()                            /* the interrupt system */
{
 pic_init();
 pic_install(1,trap);
 pic_enable(1);
 sys_sti();
}

int main()
{
 init(); 
 while(1)                              /* the normal thread main loop */
 {
  ascii_put(Screen,ch);
 }
 return 0;
}

