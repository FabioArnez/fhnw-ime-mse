/*------------------------
 gic-test
 (c) H.Buchmann FHNW 2012
 $Id$
 -------------------------*/
#include "sys/gic.h"
#include "sys/timer.h"
#include "sys/sys.h"
#include <stdio.h>

static void timer()
{
 TIMER0.Load=0x10000;
 TIMER0.Control=(0<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* one shot */
		    0;
 TIMER0.Control|=(1<<7)|  /* enable */
                 (1<<5)|  /* int enable */
		     0;
 while(TIMER0.RIS==0){}

 printf("Value=%x RIS=%x\n",TIMER0.Value,TIMER0.RIS);
}

int main()
{
 sys_irq(1);
 sys_fiq(1);
 gic_init();
 gic_enable(0x24);
 timer();
 gic_info();
 gic_active();
 return 0; 
}

