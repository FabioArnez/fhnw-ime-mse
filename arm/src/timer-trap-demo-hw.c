/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/DUI0159B_integratorcp_1_0_ug.pdf
------------------------*/
#include "stdio.h"
#include "sys/sys.h"
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
 printf("tick %d\n",cnt++);
}

void main()
{
 TIMER0->load=1<<23;
 TIMER0->control=(0<<0)| /* wrapping mode */
                 (1<<1)| /* 32 bit counter */
		 (0<<2)| /* prescale 0 */
		 (1<<5)| /* IE */
		 (1<<6)| /* periodic */
		 (1<<7); /* enable */
 while(cnt<20)           /* for terminating */
 {
 }
} 