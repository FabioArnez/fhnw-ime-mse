/*--------------------
  undef-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/sys.h" /* for triggering undef */
int main()
{
 unsigned v=0;
 while(1)
 {
  printf("trap-demo %d\n",v++);
  sys_undef();
 } 
}  
