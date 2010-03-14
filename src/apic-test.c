/*-------------------
 apic-test
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
#include "sys/apic.h"
#include "sys/trap.h"
#include "sys/sys.h"
int main()
{
 trap_init(); 
// apic_init();
// apic_timer();
 sys_sti();
 while(1)
 {
 }
 return 0;
} 
