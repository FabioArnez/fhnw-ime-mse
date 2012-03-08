/*--------------------
  undef-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/arm.h" /* for triggering undef */

#if 0
static __attribute__((interrupt("UNDEF")))void myUndef()
{
 printf("myUndef %x\n",arm_get_lr());
/*  while(1){} */
}
#endif
int main()
{
 unsigned v=0;
// arm_set_exception(UNDEF,myUndef);
 while(1)
 {
  printf("undef-trap-demo %d\n",v++);
  arm_undef(); /* call undef */
 }
}  
