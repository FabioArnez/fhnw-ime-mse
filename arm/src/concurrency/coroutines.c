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

unsigned uartPool[0x400];
Coroutine uartCo;

Coroutine mainCo;

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
  coroutine_transfer(&clockCo,&uartCo);
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
  coroutine_transfer(&uartCo,&clockCo);
 }
}


int main()
{
 coroutine_init(do_clock,clockPool,sizeof(clockPool),&clockCo);
 coroutine_init(do_uart, uartPool, sizeof(uartPool) ,&uartCo);
 coroutine_transfer(&mainCo,&clockCo);
 return 0; 
}
