/*---------------------------
 thread-demo
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
#include "sys/thread.h"
#include "stdio.h"

void run()
{
 while(1)
 {
  printf("th1\n");
  thread_yield();
 }
}

Thread th1;
unsigned pool[0x200];

int main()
{
 thread_init(&th1,run,pool,sizeof(pool));
 while(1)
 {
  printf("th0\n");
  thread_yield();
 } 
}
