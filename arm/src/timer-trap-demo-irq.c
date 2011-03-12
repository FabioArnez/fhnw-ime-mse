/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/DUI0159B_integratorcp_1_0_ug.pdf
------------------------*/
#include "stdio.h"
#include "sys/sys.h"
volatile struct                                     /* see [1] 3.6.1 */
{
 const unsigned STAT;
 const unsigned RSTAT;
 unsigned ENSET;
 unsigned ENCLR;
}* PRIMIRQ = 0x14000000;

volatile struct /* [1] 4.9.2 */
{
       unsigned load;
 const unsigned value;
       unsigned control;
       unsigned intClr;
 const unsigned RIS;
 const unsigned MIS;
       unsigned BGload;
}* TIMER0 = 0x13000000;

static unsigned cnt=0;

void onTick()
{
 TIMER0->intClr=0; /* simply write */
 printf("tick %d\n",cnt++);
}

void main()
{
 PRIMIRQ->ENSET=(1<<5); /* bit TIMERINT0 see [1] 3.6 */
 TIMER0->load=(1<<23)+100;
 TIMER0->control=(0<<0)| /* wrapping mode */
                 (1<<1)| /* 32 bit counter */
		 (0<<2)| /* prescale 0 */
		 (1<<5)| /* IE */
		 (1<<6)| /* periodic */
		 (1<<7); /* enable */
 while(cnt<20)           /* for terminating */
 {
  if (PRIMIRQ->STAT)
     {
      onTick();
     }
 }
} 
