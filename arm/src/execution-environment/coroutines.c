/*--------------------
  coroutines
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"
#include "sys/coroutine.h"
#include "stdio.h"

unsigned clockPool[0x400];
Coroutine clockCo;

unsigned echoPool[0x400];
Coroutine echoCo;

static void do_clock()
{
 Time  t={23,59,55};
 Clock clock;           /* clock now local */
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
 while(1)
 {
  if (TIMER0.RIS) 
     {
      clock_tick(&clock);
      clock_display(&clock);
      TIMER0.IntClr=0;
     }
  coroutine_transfer(&clockCo,&echoCo); /* explicit transfer */
 }    
}


static void do_echo()
{
 uart_init();
 while(1)
 {
  if (uart_avail())
     {
      uart_out(uart_in());
     }
  coroutine_transfer(&echoCo,&clockCo); /* explicit transfer */
 }
}


int main()
{
 Coroutine mainCo;
 coroutine_init(do_clock,clockPool,sizeof(clockPool),&clockCo);
 coroutine_init(do_echo, echoPool, sizeof(echoPool) ,&echoCo);
 coroutine_transfer(&mainCo,&echoCo);
 return 0; 
}
