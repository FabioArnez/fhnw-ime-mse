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


static void show()
{
 printf("main=%p\n",&main_);
 printf("run =%p\n",run);
 printf("ready\n");
 Thread* th=ready.first;
 while(th!=0)
 {
  printf("\tth=%p\n",th);
  th=th->next;
 }
}

void thread_ready(Thread* th)
{
/*<<<<<<<<<<<<<<<<<<<<<<< critical  */
 ready.last->next=th;
 ready.last=th;
/*>>>>>>>>>>>>>>>>>>>>>>> critical */ 
#if 0
 Thread* l=swap(th,&ready.last);
 l->next=th;
#endif
}

void thread_create(Thread* th,
                   void (*run)(),
                   void* pool,
		   unsigned size_byte)
{
 th->next=0;
 coroutine_init(run,pool,size_byte,&(th->cor));
 printf("create %p\n",th);
 thread_ready(th);
}

void thread_yield()
{
 Thread* r=run;
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

void thread_run() 
{
 while(1) thread_yield();
}

