/*-------------------
 apic-test
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
#include "sys/apic.h"
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"

static unsigned cnt=0;
void tick(unsigned id)
{
 ascii_printf(Screen,"tick %d\n",++cnt);
}

int main()
{
 apic_init();
 apic_timer(0x40000000,tick);
 apic_timer_enable();
 sys_sti();
 while(1)
 {
 }
 return 0;
} 
