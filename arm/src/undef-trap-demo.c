/*--------------------
  undef-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/sys.h" /* for triggering undef */
#include "sys/deb.h"

void onMyUndef()
{
 deb_signal1();
}

typedef void (*OnUndef)();

extern OnUndef onUndef; /* see big-bang.S*/	

void registerUndef(OnUndef oud)
{
 onUndef=oud;
}

int main()
{
 unsigned v=0;
 registerUndef(onMyUndef);
 printf("%p\n",*onUndef);
#if 1 
 while(1)
 {
  printf("trap-demo %d\n",v++);
  sys_undef();
 }
#endif
}  
