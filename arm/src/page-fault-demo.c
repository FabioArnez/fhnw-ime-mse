/*----------------------
  page-fault-demo
  (c) H.Buchmann FHNW 2012
  $Id$
------------------------*/
#include "stdio.h"
#include "sys/arm.h"
static __attribute__((interrupt("ABORT"))) void onData()
{
}

int main()
{
 arm_init(); /* dont forget */
 unsigned* p=(unsigned*)(64*(1<<20)); /* no memory there: see mmc.c */
 printf("before assignment\n");
 *p=0;
 printf("after assignment\n");
 return 0;
}  
