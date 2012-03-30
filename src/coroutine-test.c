/*-----------------------
 coroutine-test
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/
#include "stdio.h"
#include "sys/coroutine.h"
#include "sys/arm.h"

Coroutine c0;
Coroutine c1;

#define POOL 256
unsigned pool[POOL];

void coroutine()
{
 while(1)
 {
  printf("c1\n");
  coroutine_transfer(&c1,&c0);
 }
}

int main()
{
 arm_init();
 coroutine_init(coroutine,pool,sizeof(pool),&c1);
 while(1)
 {
  coroutine_show(&c0);
  coroutine_transfer(&c0,&c1);
  coroutine_show(&c0);
  break;
 }
 printf("--------- done\n");
 return 0;
}
 
