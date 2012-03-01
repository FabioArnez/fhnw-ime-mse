/*------------------------
 timer-test
 (c) H.Buchmann FHWN 2012
 $Id$
 -------------------------*/
#include "sys/timer.h"
#include <stdio.h>

int main()
{
 TIMER0.Control=(0<<7) | /* disabled */
                (1<<1) | /* 32 bit */
		    0;
 TIMER0.Load=0xffffffff;
 TIMER0.Control|=(1<<7); /* enable */
 while(1)
 {
  printf("Value=%x\n",TIMER0.Value);
 }
 return 0; 
}
  
