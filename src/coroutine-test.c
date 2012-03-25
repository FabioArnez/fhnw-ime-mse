/*-----------------------
 coroutine-test
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/
#include "stdio.h"
#include "sys/coroutine.h"

Coroutine c0;
Coroutine c1;

#define POOL 256
unsigned pool[POOL];

void coroutine()
{
 while(1)
 {
  coroutine_transfer(&c1,&c0);
 }
}

int main()
{
 coroutine_init(coroutine,pool,sizeof(pool),&c1);
 printf("pool=%p\n",pool);
 coroutine_show(&c1);
 return 0;
 
 while(1)
 {
  coroutine_transfer(&c0,&c1);
 }
 return 0;
}
 
