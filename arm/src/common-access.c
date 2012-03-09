/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
------------------------*/
#include "stdio.h"
#include "sys/timer.h"
#include "sys/gic.h"
#include "sys/arm.h"
#include "io/uart.h"

#define TIMER_0_1 36

volatile static int tick=0;

static void onTick()        /* the call back */
{
 ++tick;
 TIMER0.IntClr=0; /* write simply something */
}

static void init()
{
 arm_irq(1);
 gic_init();
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 TIMER0.Load=0x1000; /* the count */
 TIMER0.Control=(1<<7) | /* enabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(1<<5) | /* interrupt enable
		(0<<0) | /* wrapping */
		    0;
}


static void wait(unsigned cnt) /* use TIMER1 for busy wait */
{
 TIMER1.Load=cnt;
 TIMER1.Control=(1<<7)|
                (1<<1)|
		(1<<0)| /* one shot */
		  0;
 while(TIMER1.RIS==0){}
 TIMER1.IntClr=0;
}

static void loop()
{
 while(1)
 {
  volatile int local=tick;
  if (local)
     {
      --local;
      wait(0x100);
      if ((local+1)!=tick) printf("%d\n",tick-local);
      tick=local;
     }
 }
}

int main()
{
 init();
 loop();
 return 0; 
} 
