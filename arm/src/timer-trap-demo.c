/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/DUI0159B_integratorcp_1_0_ug.pdf
------------------------*/
#include "stdio.h"

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

void main()
{
 TIMER0->load=0xffff;
 TIMER0->control=(0<<0)| /* wrapping mode */
                 (0<<1)| /* 16 bit counter */
		 (0<<2)| /* prescale 0 */
		 (0<<5)| /* no interrupt */
		 (1<<6)| /* periodic */
		 (1<<7); /* enable */
 while(1)
 {
  printf("%x\n",TIMER0->value);
 }
} 
