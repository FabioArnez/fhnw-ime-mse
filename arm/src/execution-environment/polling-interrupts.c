/*--------------------
  polling-interrupts
  see polling.c
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/arm.h"
#include "sys/gic.h"
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"
#include "stdio.h"
#include "sys/deb.h"

#define TIMER_0_1 36
Time  t={23,59,55};
Clock clock;  

static volatile unsigned tick=0;

static void onTick()
{
 ++tick;
 TIMER0.IntClr=0;
}


static void do_clock() 
{
 if (tick>0) 
    {
/*<<<<<<<<<<<<<<<< critical */
     --tick;
/*>>>>>>>>>>>>>>>> critical */
     clock_tick(&clock);
     clock_display(&clock);
    }
}


static void do_echo()
{
 if (uart_rx_size()>0)
    {
     uart_out(uart_get()); 
    }
}




int main()
{
 arm_init();
 gic_init();
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock); 
 

 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 uart_start();
 arm_irq(1);

 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		(1<<5) | /* interrupt enable */
		    0;
 while(1) /* main loop */
 {
  do_clock();
  do_echo();
 }
 return 0; 
}
