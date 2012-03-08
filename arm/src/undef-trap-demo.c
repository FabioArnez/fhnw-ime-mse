/*--------------------
  undef-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/arm.h" /* for triggering undef */

int main()
{
 unsigned v=0;
 while(1)
 {
  printf("undef-trap-demo %d\n",v++);
  arm_undef(); /* call undef */
 }
}  
