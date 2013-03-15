/*--------------------
  threads-interrupt
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/arm.h"
#include "sys/timer.h"
#include "io/uart.h"
#include "clock.h"
#include "sys/thread.h"
#include "sys/gic.h"
#include "stdio.h"

unsigned clockPool[0x400];
unsigned echoPool[0x400];

WaitQueue clockQ;

#define TIMER_0_1 36
static volatile unsigned tick=0;
static void onTick()
{
 ++tick;
 TIMER0.IntClr=0;
 thread_ready_from(&clockQ);
}

static void do_clock()
{
 thread_wait_init(&clockQ,0,0);
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 Time  t={23,59,55};
 Clock clock;  
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
 		(1<<5) | /* interrupt enable */
		    0;
 while(1)
 {
  thread_wait_at(&clockQ);
  clock_tick(&clock);
  clock_display(&clock);
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
  thread_yield(); /* release cpu */
 }
}


int main()
{
 arm_init();
 gic_init();
 arm_irq(1);
 Thread clockTh;
 Thread echoTh;
 thread_create(&clockTh,do_clock,clockPool,sizeof(clockPool));
 thread_create(&echoTh, do_echo, echoPool, sizeof(echoPool));
 thread_run();
 return 0; 
}
