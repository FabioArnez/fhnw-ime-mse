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

static void do_clock()
{
 if (TIMER0.RIS) 
    {
     onTick();
    }
}

static void onChar(char ch)
{
 uart_out(ch);
}

static void do_uart()
{
 if (uart_avail())
    {
     onChar(uart_in());
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
 clock_show(&clock);
 while(1)
 {
  do_clock();
  do_uart();
 }
 return 0; 
}
