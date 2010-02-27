/*-------------------------
start
(c) H.Buchmann FHNW 2009
$Id$
see big-bang
---------------------------*/
#include "sys/screen.h"

void start() __attribute__((noreturn));

extern int main();

extern unsigned stack;		   /* see linker script iso.ld */
extern unsigned load_end_addr[];
extern unsigned bss_end_addr[];

/* dummy functions for cygwin */
void _alloca()
{
}

void __main()
{
}

/* we are in protected mode */
void start()
{
//---------------------- init bss
 for(unsigned* v=load_end_addr;v!=bss_end_addr;v++)*v=0;
//---------------------- initialize
 screen_init();
 main();
 while(1){}
}
