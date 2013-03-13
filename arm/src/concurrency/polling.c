/*--------------------
  polling
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"

Clock clock;  

static void onTick()
{
 clock_tick(&clock);
 clock_show(&clock);
 TIMER0.IntClr=0;
}

Time  t={0,0,0};
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
 clock_show(&clock);
 while(1)
 {
  if (TIMER0.RIS) 
     {
      onTick();
     }
  if (uart_avail())
     {
      uart_out(uart_in());
     }
 }
 return 0; 
}
