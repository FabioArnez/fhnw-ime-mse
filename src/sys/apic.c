/*-----------------------------
 apic advanced programmable interrupt controller
 (c) H.Buchmann FHNW 2010
 $Id$
 see apic-devel
 [1] Intel® 64 and IA-32 Architectures
     Software Developer's Manual 3A Chapter 8
 ------------------------------*/
#include "sys/apic.h"
#include "sys/pic.h"
#include "sys/sys.h"
#include "io/ascii.h"
#include "sys/screen.h"

typedef unsigned Entry[4];  /* 16 bytes */

/* the apic register */
static volatile Entry* apic=0;  /* will be set in apic_init */
                                           /* see table 8.1 */
                                 /* TODO explain addressing */
void apic_init()
{
 if (apic) return;                   /* already initialized */
 pic_init();
 static const MSR MASK=(1<<12)-1;
 MSR base=sys_read_msr(0x1b); /*  [1] 8.4.2 */
 apic=(volatile Entry*)((unsigned)(base&~MASK));
}


void apic_timer()
{
// *apic[0x0f]|=(1<<8);
 *apic[0x38] =0x80000000;
 *apic[0x32] =(0x20|       /* vector */
            (0<<16)|       /* unmask */
  	     (1<<17));     /* periodic */
 
 ascii_printf(Screen,"---------- l1\n");
 sys_sti();
 ascii_printf(Screen,"---------- l2\n");
 while(1)
 {
  ascii_printf(Screen,"%x %x\n",*apic[0x39],*apic[0x32]);
 }
}
