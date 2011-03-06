/*------------------------
  kbdc-demo keyboard controller demo
  (c) H.Buchmann FHNW 2011
  $Id$
--------------------------*/
#include "sys/sys.h" /* for sys_inb sys_outb */
#include "stdio.h"
void main()
{
/* 1c 1d */
 unsigned stat0=sys_inb(0x64);
 printf("%x\n",stat0); /* status */
 
 while(1)
 {
  unsigned stat1=sys_inb(0x64);
  if (stat0!=stat1)
     {
      printf("%x\n",stat1); /* status */
     }
  stat0=stat1;
 }
}
  
