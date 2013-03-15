/*--------------------
  polling
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"

Clock clock;        /* global */

static void do_clock()
{
 if (TIMER0.RIS) 
    {
     clock_tick(&clock);
     clock_display(&clock);
     TIMER0.IntClr=0;
    }
}

static void do_echo()
{
 if (uart_avail())
    {
     uart_out(uart_in()); 
    }
}

Time  t={23,59,55};

int main()
{
 uart_init();
 clock_init();
 clock_create(&clock,&t,50,50);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
 clock_display(&clock);
 while(1)
 {
  do_clock();
  do_echo();
 }
 return 0; 
}
