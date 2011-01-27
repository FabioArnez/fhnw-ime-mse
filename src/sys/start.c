/*-------------------------
start
(c) H.Buchmann FHNW 2009
$Id$
see big-bang
---------------------------*/
#include "sys/screen.h"

void _start() __attribute__((noreturn));

extern int main();

extern unsigned stack;		   /* see linker script iso.ld */
extern unsigned bss_start_addr[];
extern unsigned bss_end_addr[];

/* dummy functions for cygwin */
void _alloca()
{
}

void __main()
{
}

void _start()                            /* called from bigBang */
{
//---------------------- init bss
 for(unsigned* v=bss_start_addr;v!=bss_end_addr;v++)*v=0;
//---------------------- initialize
 main();                                           /* call main */
}
