/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 $Id$
----------------------------*/
#include "sys/thread.h"
#include "stdio.h"


static Thread* swap(Thread* in,volatile Thread** loc)
{
 Thread* out;
 asm volatile 
 (
 "@------------------------------\n"
 "\tswp %[out],%[in],[%[loc]]\n"
 :[out] "=&r" (out)     /* out */
 :[loc]"r" (loc),   /* in  */
  [in]  "r" (in)
 );
}

static Thread      main_={next:0};

static struct 
{
 Thread n0;
 Thread n1;
          Thread* first;
 volatile Thread* last; /*accessible by fore and background */
} ready =            /* n0 -> n1 
                        ^     ^
			first last */
{
 n0:    {next:&ready.n1},
 n1:    {next:0},
 first: &ready.n0,
 last:  &ready.n1
};

static Thread*     run=&main_;

void thread_ready(Thread* th)
{
 Thread* l=swap(th,&ready.last);
 l->next=th;
}

void thread_create(Thread* th,
                   void (*run)(),
                   void* pool,
		   unsigned size_byte)
{
 th->next=0;
 coroutine_init(run,pool,size_byte,&(th->cor));
 thread_ready(th);
}

void thread_yield()
{
  
 Thread* r=run;
 while(1)
 {
  thread_ready(r);
  Thread* th=ready.first;
  ready.first=th->next;
  if ((th!=&ready.n0) && (th!=&ready.n1)) 
     {
      run=th;
      coroutine_transfer(&(r->cor),&(run->cor));
     }
  thread_ready(th);   
 }
}

void thread_run() 
{
 while(1) thread_yield();
}
