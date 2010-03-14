/*----------------------
 common-access 
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


static volatile unsigned count=0;

static void trap(unsigned id)
{
 sys_inb(0x64);
 sys_inb(0x60);                 /* empty keyboard ready for next char */
 ++count;
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
  volatile unsigned v=count;
  sys_wait(1<<3);                                   /* wait a little */
  ++v;
  if (v!=(count+1)) ascii_put(Screen,'x');
  count=v;
 }
 return 0;
}

