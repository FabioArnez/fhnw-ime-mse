/*----------------------
 accessing-hardware
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/DUI0138E_CMxx6_UserGuide.pdf
----------------------*/  

volatile unsigned* CM_CTRL=(volatile unsigned*)0x1000000c;
/* 
Core Module Control  [1] p89 
                     [1] p123 (5.11)
       1               0		     
bitpos fedcba9876543210fedcba9876543210
       |                          |||||---- R/W LED 0:off 1:on
       |                          ||||----- R   mounted
       |                          |||------ R/W remap [1] 4.9
       |                          ||------- W   1: reset 
       |--------------------------|-------- reserved                    
*/

void led_on()
{
 *CM_CTRL|=(1<<0); /* set bit */
}

void led_off()
{
 *CM_CTRL&=~(1<<0); /* clear bit */
}

void wait()
{
 for(unsigned i=0;i<0x1000;++i)
 {
  volatile unsigned u=0;
 }
}

void main()
{
 while(1)
 {
  led_on();
  wait();
  led_off();
  wait();
 }
}

