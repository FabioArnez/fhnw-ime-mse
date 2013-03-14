/*--------------------
  thread
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"
#include "sys/thread.h"
#include "stdio.h"

unsigned clockPool[0x400];
unsigned uartPool[0x400];

Clock clock;  

static void onTick()
{
 clock_tick(&clock);
 clock_display(&clock);
 TIMER0.IntClr=0;
}

static void do_clock()
{
 Time  t={23,59,55};
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
      onTick();
     }
  thread_yield(); /* release cpu */
 }    
}

static void onChar(char ch)
{
 uart_out(ch);
}

static void do_uart()
{
 uart_init();
 while(1)
 {
  if (uart_avail())
     {
      onChar(uart_in());
     }
  thread_yield(); /* release cpu */
 }
}


int main()
{
 Thread clockTh;
 Thread uartTh;
 thread_create(&clockTh,do_clock,clockPool,sizeof(clockPool));
 thread_create(&uartTh, do_uart, uartPool, sizeof(uartPool));
 thread_run();
 return 0; 
}
