/*-------------------
 apic-test
 (c) H.Buchmann FHNW 2009
 $Id: apic-devel.c 186 2010-03-06 17:22:16Z hans.buchmann $
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
