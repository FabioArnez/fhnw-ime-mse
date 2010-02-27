/*----------------------
 kbc-demo (keyboard controller)
 (c) H.Buchmann FHNW 2009
 $Id$
 TODO easy to use api 
 TODO LED control
------------------------*/
#include "sys/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/io.h"                                        /* for sti */
#include "io/kbd.h"                                   /* the keyboard */

static void trap(unsigned id)
{
 ascii_string(Screen,"key\n");
}

int main()
{
 pic_init();
 pic_install(1,trap);
 sys_sti();
 
 while(1)
 {
  kbd_get();
 }
 return 0;
}

